FROM centos:6

RUN yum -q -y update && yum -q clean all

RUN yum -q -y install epel-release && \
    yum -y install git make gcc-c++ cmake qpid-proton-cpp-devel python-qpid-proton && \
    yum -q clean all

RUN mkdir /root/src

WORKDIR /root/src

ADD client.cpp Makefile brokerlib.py test.sh /root/src/

CMD ["make", "test"]
