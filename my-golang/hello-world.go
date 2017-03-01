package main

import (
  "io"
  "net/http"
)

func all(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "<html><body><div style='position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Arial, Helvetica, sans-serif;color: orange;font-size: 40px;'>Hello, World! ... brought to you by GO</div></body></html>")
}

func main() {
	http.HandleFunc("/", all)
	http.ListenAndServe(":8001", nil)
}

