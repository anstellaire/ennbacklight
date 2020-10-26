#-------------------------------------------------------------------------------
# PKG INFO
#-------------------------------------------------------------------------------

pkgname=ennbacklight
pkgver=0.1.0
pkgrel=1

pkgdesc="A simple backlight control"
arch=("x86_64")

url="https://github.com/anstellaire/ennbacklight"
license=("MIT")

provides=('ennbacklight')
conflicts=()
replaces=()

depends=()
optdepends=()
makedepends=('tar' 'make')

#-------------------------------------------------------------------------------
# PKG RULES
#-------------------------------------------------------------------------------

build() {
  cd ..
  make
}

package() {
  cd ..
  mkdir -p "$pkgdir/usr/bin/"
  cp $pkgname "$pkgdir/usr/bin/$pkgname"
}
