using System;
using System.IO;
using System.Net;
using System.Text;
using System.Threading.Tasks;

class HelloWorld
{
    static async Task Main(string[] args)
    {
        var listener = new HttpListener();
        listener.Prefixes.Add("http://*:8080/");
        listener.Start();

        Console.WriteLine("Server running on port 8080...");

        while (true)
        {
            var context = await listener.GetContextAsync();
            var request = context.Request;
            var response = context.Response;

            string html = "<html><head><style>#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #6B4C9A;font-size: 40px; }</style></head><body><div id='main'>Hello, World! ... brought to you by C#</div></body></html>";
            string css = "#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #6B4C9A;font-size: 40px; }";

            if (request.Url.AbsolutePath == "/style.css")
            {
                response.ContentType = "text/css";
                response.ContentEncoding = Encoding.UTF8;
                await response.OutputStream.WriteAsync(Encoding.UTF8.GetBytes(css), 0, css.Length);
            }
            else
            {
                response.ContentType = "text/html; charset=utf-8";
                response.ContentEncoding = Encoding.UTF8;
                await response.OutputStream.WriteAsync(Encoding.UTF8.GetBytes(html), 0, html.Length);
            }

            response.Close();
        }
    }
}
