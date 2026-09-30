use std::io::prelude::*;
use std::net::TcpListener;
use std::net::TcpStream;

fn main() {
    let listener = TcpListener::bind("0.0.0.0:8080").unwrap();

    for stream in listener.incoming() {
        let stream = stream.unwrap();

        handle_connection(stream);
    }
}

fn handle_connection(mut stream: TcpStream) {
    let mut buffer = [0; 1024];

    stream.read(&mut buffer).unwrap();

    let request = String::from_utf8_lossy(&buffer[..]).to_string();
    let first_line: String = request.lines().next().unwrap_or("").to_string();
    let path: Vec<&str> = first_line.split_whitespace().collect();

    if path.len() >= 2 && path[0] == "GET" && path[1] == "/" {
        let response = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n".to_string() + include_str!("index.html");
        stream.write_all(response.as_bytes()).unwrap();
    } else if path.len() >= 2 && path[0] == "GET" && path[1] == "/style.css" {
        let response = "HTTP/1.1 200 OK\r\nContent-Type: text/css\r\n\r\n".to_string() + include_str!("style.css");
        stream.write_all(response.as_bytes()).unwrap();
    }

    stream.flush().unwrap();
}
