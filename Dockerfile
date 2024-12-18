FROM alpine AS build
RUN apk add --no-cache build-base automake autoconf libtool git
WORKDIR /home/myprogram
RUN git clone --branch branchHTTPserverMulti https://github.com/IlyaMaluk/devops.git .
RUN aclocal
RUN autoconf
RUN chmod +x configure
RUN ./configure
RUN make

FROM alpine 
COPY --from=build /home/myprogram/devops/my_program /usr/local/bin/my_program
ENTRYPOINT ["/usr/local/bin/my_program"]




