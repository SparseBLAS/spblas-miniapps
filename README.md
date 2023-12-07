'spblas-miniapps' requires LAPACK++ and BLAS++ libraries; here's how to get them:

1. Download and install BLAS++:
```
git clone https://github.com/icl-utk-edu/blaspp.git
mkdir blaspp-build
cd blaspp-build
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=`pwd`/../blaspp-install \     
      -DCMAKE_BINARY_DIR=`pwd` \     
      -Dbuild_tests=OFF \    
      ../blaspp
make -j20 install
```

2. Download and install LAPACK++:
```
git clone https://github.com/icl-utk-edu/lapackpp.git
mkdir lapackpp-build
cd lapackpp-build
cmake -DCMAKE_BUILD_TYPE=Release \
        -Dgpu_backend=none \
        -Dblaspp_DIR=`pwd`/../blaspp-install/lib/cmake/blaspp/ \     
        -DCMAKE_INSTALL_PREFIX=`pwd`/../lapackpp-install \     
        -DCMAKE_BINARY_DIR=`pwd` \     
        -Dbuild_tests=OFF \     
        ../lapackpp/
make -j20 install
```

Download and install 'spblas-miniapps':
```
git clone https://github.com/SparseBLAS/spblas-miniapps.git
mkdir miniapps-build
cd miniapps-build
cmake   -Dblaspp_DIR=`pwd`/../blaspp-install/lib/cmake/blaspp/ \     
        -Dlapackpp_DIR=`pwd`/../lapackpp-install/lib/cmake/lapackpp/ \  
        -DCMAKE_INSTALL_PREFIX=`pwd`/../miniapps-install \     
        -DCMAKE_BINARY_DIR=`pwd` \          
        ../spblas-miniapps/
make -j20 install
```
