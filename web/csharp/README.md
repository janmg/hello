# Hello World - C#

A simple HTTP web server in C# using `HttpListener`.

## Running locally

```bash
dotnet run server.cs
```

Or compile and run:

```bash
dotnet build server.cs
dotnet server.dll
```

Then visit `http://localhost:8002/`

## Running with Docker

```bash
docker build -t csharp-hello .
docker run -p 8002:8002 csharp-hello
```
