use std::f32::consts::E;
use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;
use std::path::Path;

#[derive(Debug, Copy, Clone)]
pub enum Operation {
    Add,
    Subtract,
    Multiply,
    Divide,
    Modulo
}

impl Operation {
    // [COMPLETE THIS FUNCTION]
    pub fn from_char(symbol: char) -> Option<Operation> {
        return match symbol {
            '+' => Some(Operation::Add),
            '-' => Some(Operation::Subtract),
            '*' | 'x' => Some(Operation::Multiply),
            '/' => Some(Operation::Divide),
            '%' => Some(Operation::Modulo),
            _ => None
        };
    }
}

// [HELPER FUNCTION - DO NOT EDIT]
pub fn get_equation_tuple(line: &String) -> (Option<&str>, Option<&str>) {
    let v: Vec<&str> = line.split(&['-', '+', 'x', '*', '/', '%'][..]).collect();
    return (v.get(0).cloned(), v.get(1).cloned())
}

// [COMPLETE THIS HELPER FUNCTION]
pub fn parse_equation(line: &String) -> Result<(f32, f32, Operation), ()> {
    let ops = get_equation_tuple(line);
    if let (Some(op1), Some(op2)) = ops {
        if let (Ok(op1), Ok(op2)) = (op1.trim().parse::<f32>(), op2.trim().parse::<f32>()) {
            for c in line.chars() {
                if let Some(op) = Operation::from_char(c) {
                    return Ok((op1, op2, op));
                }
            }
        }
        return Err(());
    }
    return Err(());
}

// [COMPLETE THIS FUNCTION]
pub fn solve(equation: &String) -> Result<f32, ()> {
    if let Ok(parsed) = parse_equation(equation) {
        return match parsed.2 {
            Operation::Add => Ok(parsed.0 + parsed.1),
            Operation::Subtract => Ok(parsed.0 - parsed.1),
            Operation::Multiply => Ok(parsed.0 * parsed.1),
            Operation::Divide => Ok(parsed.0 / parsed.1),
            Operation::Modulo => Ok(parsed.0 % parsed.1)
        }
    }
    return Err(());
}

// [COMPLETE THIS FUNCTION]
pub fn solve_all(file_path: &str) -> Result<f32, ()> {
    let mut ans: f32 = 0.0;
    if let Ok(lines) = read_lines(file_path) {
        for line in lines {
            if let Ok(ip) = line {
                if solve(&ip).is_ok() { ans += solve(&ip).unwrap(); }
            }
        }
        return Ok(ans);
    }
    return Err(());
}

fn read_lines<P>(filename: P) -> std::io::Result<std::io::Lines<std::io::BufReader<File>>>
where P: AsRef<Path>, {
    return Ok(std::io::BufReader::new(File::open(filename)?).lines())
}