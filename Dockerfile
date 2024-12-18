FROM alpine AS build
RUN apk add --no-cache build-base automake autoconf
WORKDIR /home/myprogram
COPY . .
RUN ./configure
RUN chmod +x configure
RUN autoreconf -i
RUN make

FROM alpine 
COPY --from=build /home/myprogram/my_program /usr/local/bin/my_program
ENTRYPOINT ["/usr/local/bin/my_program"]


