FROM golang:1.14

RUN apt-get update

RUN go get github.com/rs/cors
RUN go get github.com/gorilla/mux

WORKDIR /app
COPY . .

EXPOSE 8000

RUN go build -o main .
CMD ["/app/main"]