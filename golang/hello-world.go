package main

import (
  "io"
  "net/http"
)

func index(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Content-Type", "text/html; charset=utf-8")
    io.WriteString(w, "<html><head><link rel='stylesheet' type='text/css' href='/style.css' integrity='sha384-/C8LiakupWFy9n9Ts2ytX3de+XhmbIF5sfLEzm6YKG/RNZvQGEKACfgouPveNut7' /></head><body><div id='main'>Hello, World! ... brought to you by GO</div></body></html>")
}

func css(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Content-Type", "text/css; charset=utf-8")
    io.WriteString(w, "#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: orange;font-size: 40px; }")
}

func main() {
    http.HandleFunc("/", index)
    http.HandleFunc("/style.css", css)
    http.ListenAndServe(":8080", nil)
}

