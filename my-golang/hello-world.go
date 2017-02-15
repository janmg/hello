package main
 
import (
  "fmt"
  "log"
  "net/http"
)
 
func main() {
  http.HandleFunc("/", func(w http.ResponseWriter, req *http.Request) {
    fmt.Fprintln(w, "Hello World, brought to you by GO!")
  })
  log.Fatal(http.ListenAndServe(":8001", nil))
}
