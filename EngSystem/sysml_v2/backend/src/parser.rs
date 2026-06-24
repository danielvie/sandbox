use serde::Serialize;
use tree_sitter::{Node, Parser};

#[derive(Debug, Serialize, Clone, PartialEq)]
pub struct SysmlModel {
    pub packages: Vec<Package>,
    pub errors: Vec<ParseError>,
}

#[derive(Debug, Serialize, Clone, PartialEq)]
pub struct Package {
    pub name: String,
    pub start_line: usize,
    pub end_line: usize,
    pub start_byte: usize,
    pub end_byte: usize,
    pub body_end_byte: Option<usize>,
    pub parts: Vec<Part>,
    pub connections: Vec<Connection>,
}

#[derive(Debug, Serialize, Clone, PartialEq)]
pub struct Part {
    pub name: String,
    pub start_line: usize,
    pub end_line: usize,
    pub start_byte: usize,
    pub end_byte: usize,
    pub name_start_byte: usize,
    pub name_end_byte: usize,
    pub body_end_byte: Option<usize>,
    pub attributes: Vec<Attribute>,
    pub ports: Vec<Port>,
}

#[derive(Debug, Serialize, Clone, PartialEq)]
pub struct Port {
    pub name: String,
    pub start_line: usize,
    pub end_line: usize,
    pub start_byte: usize,
    pub end_byte: usize,
    pub name_start_byte: usize,
    pub name_end_byte: usize,
}

#[derive(Debug, Serialize, Clone, PartialEq)]
pub struct Attribute {
    pub name: String,
    pub start_line: usize,
    pub end_line: usize,
    pub start_byte: usize,
    pub end_byte: usize,
    pub name_start_byte: usize,
    pub name_end_byte: usize,
}

#[derive(Debug, Serialize, Clone, PartialEq)]
pub struct Connection {
    pub name: Option<String>,
    pub source: String,
    pub target: String,
    pub start_line: usize,
    pub end_line: usize,
    pub start_byte: usize,
    pub end_byte: usize,
}

#[derive(Debug, Serialize, Clone, PartialEq)]
pub struct ParseError {
    pub message: String,
    pub line: usize,
    pub column: usize,
}

fn get_identifier_node<'a>(node: Node<'a>) -> Option<Node<'a>> {
    if node.kind() == "identifier" {
        return Some(node);
    }
    let mut cursor = node.walk();
    for child in node.children(&mut cursor) {
        if let Some(n) = get_identifier_node(child) {
            return Some(n);
        }
    }
    None
}

fn find_first_descendant_by_kind<'a>(node: Node<'a>, kind: &str) -> Option<Node<'a>> {
    if node.kind() == kind {
        return Some(node);
    }
    let mut cursor = node.walk();
    for child in node.children(&mut cursor) {
        if let Some(descendant) = find_first_descendant_by_kind(child, kind) {
            return Some(descendant);
        }
    }
    None
}

pub fn collect_errors(node: Node, source: &str, errors: &mut Vec<ParseError>) {
    if node.kind() == "ERROR" || node.is_error() {
        let start = node.start_position();
        let text = node.utf8_text(source.as_bytes()).unwrap_or("");
        let msg = if text.trim().is_empty() {
            "Syntax error".to_string()
        } else {
            format!("Syntax error near: '{}'", text.trim_end())
        };
        errors.push(ParseError {
            message: msg,
            line: start.row + 1,
            column: start.column + 1,
        });
    } else if node.is_missing() {
        let start = node.start_position();
        errors.push(ParseError {
            message: format!("Missing element of type '{}'", node.kind()),
            line: start.row + 1,
            column: start.column + 1,
        });
    } else {
        let mut cursor = node.walk();
        for child in node.children(&mut cursor) {
            collect_errors(child, source, errors);
        }
    }
}

pub fn parse_sysml(source: &str) -> SysmlModel {
    let mut parser = Parser::new();
    let language = tree_sitter_sysml::LANGUAGE;
    parser
        .set_language(&language.into())
        .expect("Error loading SysML parser");

    let tree = parser.parse(source, None).unwrap();
    let root_node = tree.root_node();

    let mut errors = Vec::new();
    collect_errors(root_node, source, &mut errors);

    let mut packages = Vec::new();
    let mut cursor = root_node.walk();

    for child in root_node.children(&mut cursor) {
        if child.kind() == "package_definition" {
            if let Some(pkg) = parse_package(child, source) {
                packages.push(pkg);
            }
        }
    }

    SysmlModel { packages, errors }
}

fn parse_package(node: Node, source: &str) -> Option<Package> {
    let start_pos = node.start_position();
    let end_pos = node.end_position();

    let name_node = find_first_descendant_by_kind(node, "identification")?;
    let ident_node = get_identifier_node(name_node)?;
    let name = ident_node.utf8_text(source.as_bytes()).unwrap_or("").trim().to_string();

    let mut parts = Vec::new();
    let mut connections = Vec::new();
    let mut body_end_byte = None;

    if let Some(body_node) = find_first_descendant_by_kind(node, "package_body") {
        let body_text = body_node.utf8_text(source.as_bytes()).unwrap_or("");
        if body_text.contains('{') {
            body_end_byte = Some(body_node.end_byte());
            let mut body_cursor = body_node.walk();
            for element in body_node.children(&mut body_cursor) {
                match element.kind() {
                    "part_usage" => {
                        if let Some(part) = parse_part(element, source) {
                            parts.push(part);
                        }
                    }
                    "connection_usage" => {
                        if let Some(conn) = parse_connection(element, source) {
                            connections.push(conn);
                        }
                    }
                    _ => {}
                }
            }
        }
    }

    Some(Package {
        name,
        start_line: start_pos.row + 1,
        end_line: end_pos.row + 1,
        start_byte: node.start_byte(),
        end_byte: node.end_byte(),
        body_end_byte,
        parts,
        connections,
    })
}

fn parse_part(node: Node, source: &str) -> Option<Part> {
    let start_pos = node.start_position();
    let end_pos = node.end_position();

    let decl_node = find_first_descendant_by_kind(node, "usage_declaration")?;
    let ident_node = get_identifier_node(decl_node)?;
    let name = ident_node.utf8_text(source.as_bytes()).unwrap_or("").trim().to_string();
    let name_start_byte = ident_node.start_byte();
    let name_end_byte = ident_node.end_byte();

    let mut attributes = Vec::new();
    let mut ports = Vec::new();
    let mut body_end_byte = None;

    if let Some(body_node) = find_first_descendant_by_kind(node, "usage_body") {
        let body_text = body_node.utf8_text(source.as_bytes()).unwrap_or("");
        if body_text.contains('{') {
            body_end_byte = Some(body_node.end_byte());
            let mut body_cursor = body_node.walk();
            for element in body_node.children(&mut body_cursor) {
                match element.kind() {
                    "attribute_usage" => {
                        if let Some(attr_decl) = find_first_descendant_by_kind(element, "usage_declaration") {
                            if let Some(attr_ident) = get_identifier_node(attr_decl) {
                                let attr_name = attr_ident.utf8_text(source.as_bytes()).unwrap_or("").trim();
                                let attr_start = element.start_position();
                                let attr_end = element.end_position();
                                attributes.push(Attribute {
                                    name: attr_name.to_string(),
                                    start_line: attr_start.row + 1,
                                    end_line: attr_end.row + 1,
                                    start_byte: element.start_byte(),
                                    end_byte: element.end_byte(),
                                    name_start_byte: attr_ident.start_byte(),
                                    name_end_byte: attr_ident.end_byte(),
                                });
                            }
                        }
                    }
                    "port_usage" => {
                        if let Some(port_ident_node) = find_first_descendant_by_kind(element, "identification") {
                            if let Some(port_ident) = get_identifier_node(port_ident_node) {
                                let port_name = port_ident.utf8_text(source.as_bytes()).unwrap_or("").trim();
                                let port_start = element.start_position();
                                let port_end = element.end_position();
                                ports.push(Port {
                                    name: port_name.to_string(),
                                    start_line: port_start.row + 1,
                                    end_line: port_end.row + 1,
                                    start_byte: element.start_byte(),
                                    end_byte: element.end_byte(),
                                    name_start_byte: port_ident.start_byte(),
                                    name_end_byte: port_ident.end_byte(),
                                });
                            }
                        }
                    }
                    _ => {}
                }
            }
        }
    }

    Some(Part {
        name,
        start_line: start_pos.row + 1,
        end_line: end_pos.row + 1,
        start_byte: node.start_byte(),
        end_byte: node.end_byte(),
        name_start_byte,
        name_end_byte,
        body_end_byte,
        attributes,
        ports,
    })
}

fn parse_connection(node: Node, source: &str) -> Option<Connection> {
    let start_pos = node.start_position();
    let end_pos = node.end_position();

    let name = if let Some(decl_node) = find_first_descendant_by_kind(node, "usage_declaration") {
        get_identifier_node(decl_node).map(|n| n.utf8_text(source.as_bytes()).unwrap_or("").trim().to_string())
    } else {
        None
    };

    let conn_part = find_first_descendant_by_kind(node, "connection_part")?;
    
    let mut endpoints = Vec::new();
    let mut cursor = conn_part.walk();
    for child in conn_part.children(&mut cursor) {
        if child.kind() == "connect_endpoint" {
            let text = child.utf8_text(source.as_bytes()).unwrap_or("").trim();
            endpoints.push(text.to_string());
        }
    }

    if endpoints.len() >= 2 {
        Some(Connection {
            name,
            source: endpoints[0].clone(),
            target: endpoints[1].clone(),
            start_line: start_pos.row + 1,
            end_line: end_pos.row + 1,
            start_byte: node.start_byte(),
            end_byte: node.end_byte(),
        })
    } else {
        None
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_valid_sysml() {
        let code = r#"
        package Example {
            part motor {
                attribute horsepower;
                port fuel_in;
            }
            part tank {
                port fuel_out;
            }
            connection c connect tank.fuel_out to motor.fuel_in;
        }
        "#;
        let model = parse_sysml(code);
        assert_eq!(model.errors.len(), 0);
        assert_eq!(model.packages.len(), 1);
        let pkg = &model.packages[0];
        assert_eq!(pkg.name, "Example");
        assert_eq!(pkg.parts.len(), 2);
        
        let motor = &pkg.parts[0];
        assert_eq!(motor.name, "motor");
        assert_eq!(motor.attributes.len(), 1);
        assert_eq!(motor.attributes[0].name, "horsepower");
        assert_eq!(motor.ports.len(), 1);
        assert_eq!(motor.ports[0].name, "fuel_in");

        let tank = &pkg.parts[1];
        assert_eq!(tank.name, "tank");
        assert_eq!(tank.ports.len(), 1);
        assert_eq!(tank.ports[0].name, "fuel_out");

        assert_eq!(pkg.connections.len(), 1);
        let conn = &pkg.connections[0];
        assert_eq!(conn.name, Some("c".to_string()));
        assert_eq!(conn.source, "tank.fuel_out");
        assert_eq!(conn.target, "motor.fuel_in");
    }

    #[test]
    fn test_parse_with_errors() {
        let code = r#"
        package Example {
            part motor {
                // missing matching braces
        "#;
        let model = parse_sysml(code);
        assert!(model.errors.len() > 0);
    }
}
