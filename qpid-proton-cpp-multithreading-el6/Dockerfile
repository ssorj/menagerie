FROM centos:6

RUN yum -q -y update && yum -q clean all

RUN yum -q -y install epel-release && \
    yum -q -y install git make gcc-c++ cmake qpid-proton-cpp-devel python-argparse python-qpid-proton && \
    yum -q clean all

RUN mkdir /root/src

WORKDIR /root/src

COPY *.cpp container.mk brokerlib.py test.sh /root/src/

CMD ["make", "-f", "container.mk", "clean", "test"]
