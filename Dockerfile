FROM ubuntu:22.04
LABEL author="Albert Álvarez Carulla <a.alvarez@onalabs.com>"

ENV CPPUTEST_HOME=/opt/cpputest
ENV LANG es_ES.UTF-8
ENV LANGUAGE es_ES.UTF-8
ENV LC_ALL es_ES.UTF-8
ENV TZ=Europe/Madrid

RUN apt-get update && \
    ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone && \
    apt-get install -y --no-install-recommends git curl unzip automake autoconf libtool build-essential clang-format lcov locales tzdata gdb bc && \
    dpkg-reconfigure -f noninteractive tzdata && \
    locale-gen es_ES.UTF-8 && \
    git clone -c http.sslverify=false https://github.com/cpputest/cpputest.git /opt/cpputest && \
    cd /opt/cpputest && \
    autoreconf . -i && \
    ./configure && \
    make tdd && \
    rm -rf /var/lib/apt/lists/* && \
    rm -rf /tmp