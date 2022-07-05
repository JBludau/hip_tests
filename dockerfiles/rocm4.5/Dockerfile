FROM rocm/dev-ubuntu-20.04:4.5

LABEL description="hip_tests/rocm4.5"

RUN apt-get update && \
# RUN apk update && \
 DEBIAN_FRONTEND=noninteractive apt-get install -yq  \
    cmake \
    git \
    && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/JBludau/hip_tests.git
RUN mkdir hip_tests/build 
RUN cd hip_tests/build && cmake \
                -DCMAKE_CXX_COMPILER=hipcc \
                -DCMAKE_CXX_FLAGS="-Wall" \
              ..
RUN cd hip_tests/build && make 
RUN echo "launch docker container with options '--device=/dev/kfd --device=/dev/dri --security-opt seccomp=unconfined --group-add video --env HIP_VISIBLE_DEVICES=0' and run ctest in hip_tests/build."
