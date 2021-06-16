# Maintainer: deutherity <deutherity@gmail.com>
pkgname=pwhash
pkgver=0.1
pkgrel=1
pkgdesc="generates exact same passwords based on your original password using hash algorithms"
arch=('any')
url="https://github.com/deutherity/pwhash"
license=('GPL')
groups=()
depends=('xclip>=0.13' 'openssl>=1')
makedepends=('cmake>=3' 'extra-cmake-modules>=5.83')
optdepends=()
provides=()
conflicts=()
replaces=()
backup=('~/.config/pwhash/pwdb.txt')
options=()
#install=
source=('git+https://github.com/deutherity/pwhash.git')
noextract=()
md5sums=('SKIP') #autofill using updpkgsums

build() {
  cd "$pkgname"
  cmake --build build
}

prepare()
{
  cd "$pkgname"
  git submodule update --recursive --init
  cmake -B ./build -DCMAKE_BUILD_TYPE=Release
}


package() 
{
  install -Dm755 "$srcdir/$pkgname/build/pwhash" "$pkgdir/usr/bin/pwhash"
}
