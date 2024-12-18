FROM alpine
WORKDIR /home/myprogram
COPY ./my_program .
RUN apk add libstdc++
RUN apk add libc6-compat
ENTRYPOINT ["./my_program"]

