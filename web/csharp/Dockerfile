FROM mcr.microsoft.com/dotnet/sdk:8.0-alpine AS builder
WORKDIR /usr/src/app
COPY server.csproj /usr/src/app/
COPY server.cs /usr/src/app/
RUN dotnet build -c Release -o out

FROM mcr.microsoft.com/dotnet/runtime:8.0-alpine

WORKDIR /usr/app
COPY --from=builder /usr/src/app/out /usr/app/

EXPOSE 8080
CMD ["dotnet", "server.dll"]
