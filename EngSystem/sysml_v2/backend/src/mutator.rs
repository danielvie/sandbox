use serde::Deserialize;

#[derive(Debug, Deserialize)]
#[serde(tag = "type")]
pub enum Mutation {
    #[serde(rename = "rename")]
    Rename {
        start_byte: usize,
        end_byte: usize,
        value: String,
    },
    #[serde(rename = "delete")]
    Delete {
        start_byte: usize,
        end_byte: usize,
    },
    #[serde(rename = "add_part")]
    AddPart {
        package_body_end_byte: usize,
        name: String,
    },
    #[serde(rename = "add_port")]
    AddPort {
        part_start_byte: usize,
        part_end_byte: usize,
        part_body_end_byte: Option<usize>,
        name: String,
    },
    #[serde(rename = "add_connection")]
    AddConnection {
        package_body_end_byte: usize,
        source: String,
        target: String,
    },
}

fn get_line_indent(code: &str, offset: usize) -> String {
    let offset = if offset > code.len() { code.len() } else { offset };
    let mut line_start = offset;
    while line_start > 0 {
        let prev = line_start - 1;
        if &code[prev..line_start] == "\n" {
            break;
        }
        line_start = prev;
    }
    let mut indent = String::new();
    for c in code[line_start..offset].chars() {
        if c == ' ' || c == '\t' {
            indent.push(c);
        } else {
            break;
        }
    }
    indent
}

fn get_whitespace_before_on_same_line(code: &str, pos: usize) -> Option<String> {
    if pos == 0 || pos > code.len() {
        return None;
    }
    let mut curr = pos;
    let bytes = code.as_bytes();
    let mut ws = Vec::new();
    while curr > 0 {
        curr -= 1;
        let b = bytes[curr];
        if b == b'\n' {
            ws.reverse();
            return Some(String::from_utf8(ws).unwrap());
        } else if b == b' ' || b == b'\t' {
            ws.push(b);
        } else {
            return None;
        }
    }
    ws.reverse();
    Some(String::from_utf8(ws).unwrap())
}

pub fn apply_mutation(code: &str, mutation: Mutation) -> String {
    match mutation {
        Mutation::Rename { start_byte, end_byte, value } => {
            if start_byte > code.len() || end_byte > code.len() || start_byte > end_byte {
                return code.to_string();
            }
            let mut new_code = String::new();
            new_code.push_str(&code[..start_byte]);
            new_code.push_str(&value);
            new_code.push_str(&code[end_byte..]);
            new_code
        }
        Mutation::Delete { start_byte, end_byte } => {
            if start_byte > code.len() || end_byte > code.len() || start_byte > end_byte {
                return code.to_string();
            }
            let mut new_code = String::new();
            new_code.push_str(&code[..start_byte]);
            new_code.push_str(&code[end_byte..]);
            new_code
        }
        Mutation::AddPart { package_body_end_byte, name } => {
            if package_body_end_byte == 0 || package_body_end_byte > code.len() {
                return format!("{}\n    part {};\n", code.trim_end(), name);
            }
            let indent = get_line_indent(code, package_body_end_byte);
            let insert_pos = package_body_end_byte - 1;
            let format_str = if let Some(ws) = get_whitespace_before_on_same_line(code, insert_pos) {
                format!("    part {};\n{}", name, ws)
            } else {
                let mut prefix = "";
                if insert_pos > 0 && &code[insert_pos - 1..insert_pos] != "\n" {
                    prefix = "\n";
                }
                format!("{}{}    part {};\n{}", prefix, indent, name, indent)
            };
            let mut new_code = String::new();
            new_code.push_str(&code[..insert_pos]);
            new_code.push_str(&format_str);
            new_code.push_str(&code[insert_pos..]);
            new_code
        }
        Mutation::AddPort { part_start_byte, part_end_byte, part_body_end_byte, name } => {
            if let Some(body_end) = part_body_end_byte {
                if body_end == 0 || body_end > code.len() {
                    return code.to_string();
                }
                let indent = get_line_indent(code, body_end);
                let insert_pos = body_end - 1;
                let format_str = if let Some(ws) = get_whitespace_before_on_same_line(code, insert_pos) {
                    format!("    port {};\n{}", name, ws)
                } else {
                    let mut prefix = "";
                    if insert_pos > 0 && &code[insert_pos - 1..insert_pos] != "\n" {
                        prefix = "\n";
                    }
                    format!("{}{}    port {};\n{}", prefix, indent, name, indent)
                };
                let mut new_code = String::new();
                new_code.push_str(&code[..insert_pos]);
                new_code.push_str(&format_str);
                new_code.push_str(&code[insert_pos..]);
                new_code
            } else {
                if part_start_byte > code.len() || part_end_byte > code.len() || part_start_byte > part_end_byte {
                    return code.to_string();
                }
                let indent = get_line_indent(code, part_start_byte);
                let decl = &code[part_start_byte..part_end_byte];
                let decl_trimmed = decl.trim_end_matches(';').trim_end();
                let replacement = format!("{} {{\n{}    port {};\n{}}}", decl_trimmed, indent, name, indent);
                let mut new_code = String::new();
                new_code.push_str(&code[..part_start_byte]);
                new_code.push_str(&replacement);
                new_code.push_str(&code[part_end_byte..]);
                new_code
            }
        }
        Mutation::AddConnection { package_body_end_byte, source, target } => {
            if package_body_end_byte == 0 || package_body_end_byte > code.len() {
                return format!("{}\n    connection connect {} to {};\n", code.trim_end(), source, target);
            }
            let indent = get_line_indent(code, package_body_end_byte);
            let insert_pos = package_body_end_byte - 1;
            let format_str = if let Some(ws) = get_whitespace_before_on_same_line(code, insert_pos) {
                format!("    connection connect {} to {};\n{}", source, target, ws)
            } else {
                let mut prefix = "";
                if insert_pos > 0 && &code[insert_pos - 1..insert_pos] != "\n" {
                    prefix = "\n";
                }
                format!("{}{}    connection connect {} to {};\n{}", prefix, indent, source, target, indent)
            };
            let mut new_code = String::new();
            new_code.push_str(&code[..insert_pos]);
            new_code.push_str(&format_str);
            new_code.push_str(&code[insert_pos..]);
            new_code
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_rename_mutation() {
        let code = "package Example {\n    part motor;\n}";
        let start_byte = code.find("motor").unwrap();
        let end_byte = start_byte + "motor".len();
        let mutated = apply_mutation(code, Mutation::Rename {
            start_byte,
            end_byte,
            value: "engine".to_string(),
        });
        assert_eq!(mutated, "package Example {\n    part engine;\n}");
    }

    #[test]
    fn test_add_port_without_body() {
        let code = "package Example {\n    part motor;\n}";
        let start_byte = code.find("part motor;").unwrap();
        let end_byte = start_byte + "part motor;".len();
        let mutated = apply_mutation(code, Mutation::AddPort {
            part_start_byte: start_byte,
            part_end_byte: end_byte,
            part_body_end_byte: None,
            name: "fuel_in".to_string(),
        });
        assert_eq!(mutated, "package Example {\n    part motor {\n        port fuel_in;\n    }\n}");
    }

    #[test]
    fn test_add_port_with_existing_ports() {
        let code = "package Example {\n    part motor {\n        port fuel_in;\n    }\n}";
        let motor_body_end = code.find("    }\n}").unwrap() + "    }".len();
        
        let mutated = apply_mutation(code, Mutation::AddPort {
            part_start_byte: code.find("part motor").unwrap(),
            part_end_byte: motor_body_end,
            part_body_end_byte: Some(motor_body_end),
            name: "fuel_out".to_string(),
        });
        
        assert_eq!(
            mutated,
            "package Example {\n    part motor {\n        port fuel_in;\n        port fuel_out;\n    }\n}"
        );
    }
}
