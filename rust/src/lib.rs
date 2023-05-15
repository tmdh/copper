use regex::Regex;
use std::ffi::{c_char, CStr, CString};

use select::document::Document;
use select::predicate::{Class, Descendant, Name};

#[repr(C)]
#[derive(Debug)]
pub struct TestCase {
    pub input: *const c_char,
    pub expected: *const c_char,
}

pub fn parse_testcase(source: &str) -> (Vec<String>, Vec<String>) {
    let document = Document::from(source);
    let re = Regex::new(r"(<br>|<br/>)").unwrap();
    let inputs: Vec<String> = document
        .find(Descendant(Class("input"), Name("pre")))
        .map(|e| e.inner_html())
        .map(|e| re.replace_all(&e, "\n").into())
        .collect();
    let outputs: Vec<String> = document
        .find(Descendant(Class("output"), Name("pre")))
        .map(|e| e.inner_html())
        .map(|e| re.replace_all(&e, "\n").into())
        .collect();
    (inputs, outputs)
}

#[no_mangle]
pub extern "C" fn parse_testcase_ffi(source: *const c_char, length: *mut usize) -> *const TestCase {
    let s_cstr = unsafe { CStr::from_ptr(source) };
    let s_str = s_cstr.to_str().unwrap();

    let (inputs, outputs) = parse_testcase(s_str);

    let mut testcases = vec![];
    for i in 0..inputs.len() {
        let input_c = CString::new(inputs[i].as_str()).unwrap();
        let output_c = CString::new(outputs[i].as_str()).unwrap();
        testcases.push(TestCase {
            input: input_c.as_ptr(),
            expected: output_c.as_ptr()
        });
        std::mem::forget(input_c);
        std::mem::forget(output_c);
    }
    unsafe { *length = testcases.len(); }
    let p = testcases.as_ptr();
    std::mem::forget(p);
    std::mem::forget(testcases);
    p
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1342d() {
        let source = include_str!("1342d.html");
        let (inputs, outputs) = parse_testcase(source);
        println!("{:?}", inputs);
        println!("{:?}", outputs);
        let c_string = CString::new(source).unwrap();
        let testcases = parse_testcase_ffi(c_string.as_ptr());
        println!("{:?}", testcases);
    }
}
