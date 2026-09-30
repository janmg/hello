FROM mcr.microsoft.com/dotnet/sdk:8.0-alpine

WORKDIR /usr/src/png
COPY PNGParser.cs /usr/src/png/Program.cs

RUN dotnet new console -f net8.0 --force && \
    dotnet build -o out

CMD ["dotnet", "out/PNGParser.dll", "/usr/src/hello/test.png"]
