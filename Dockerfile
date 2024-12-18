FROM alpine AS build
RUN apk add --no-cache build-base automake autoconf libtool
WORKDIR /home/myprogram
COPY . .
RUN autoreconf -i
RUN chmod +x configure
RUN ./configure
RUN make

FROM alpine 
COPY --from=build /home/myprogram/my_program /usr/local/bin/my_program
ENTRYPOINT ["/usr/local/bin/my_program"]




