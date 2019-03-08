# This file contains a formula for installing Poppler on Mac OS X using the
# Homebrew package manager:
#
#     http://brew.sh/
#
# To install Poppler using this formula:
#
#     brew install path/to/this/poppler.rb
#
# Changes compared to Homebrew's standard Poppler formula:
#
#   - TeXworks-specific patches are applied to
#        - help Qt apps find the poppler-data directory.
#        - use native Mac OS X font handling (instead of fontconfig)
class Poppler < Formula
  desc "PDF rendering library (based on the xpdf-3.0 code base)"
  homepage "https://poppler.freedesktop.org/"
 url "https://poppler.freedesktop.org/poppler-0.74.0.tar.xz"
  sha256 "92e09fd3302567fd36146b36bb707db43ce436e8841219025a82ea9fb0076b2f"
  head "https://anongit.freedesktop.org/git/poppler/poppler.git"

# BEGIN TEXWORKS MODIFICATION
#  bottle do
#    sha256 "cc93d0fe33c51c4b34343f5a0741dd15f5ab1267758601d82a58bdcbf7e0ee12" => :high_sierra
#    sha256 "3840e4e782fb50e889b7840c93ab338464c296f8107f3a0cbc33f3614dadf94c" => :sierra
#    sha256 "c04f2f8df8b1c79b40cc15ca192ad06b23f73d6f02114a20cd9dfc264354e4df" => :el_capitan
#  end

  version '0.74.0-texworks'

  TEXWORKS_SOURCE_DIR = Pathname.new(__FILE__).realpath.dirname.join('..')
  TEXWORKS_PATCH_DIR = TEXWORKS_SOURCE_DIR + 'lib-patches/'
  patch do
    url "file://" + TEXWORKS_PATCH_DIR + 'poppler-0001-Fix-bogus-memory-allocation-in-SplashFTFont-makeGlyp.patch'
    sha256 "0d974f87b8c0993aeb8ea70401e3b2419b7d8ee6c25b982c84bbdcb6e0152c71"
  end
  patch do
    url "file://" + TEXWORKS_PATCH_DIR + 'poppler-0002-Native-Mac-font-handling.patch'
    sha256 "40ed5889583ea4e20bdf3ed642dfb3f948224a84280593b0ced979a90464d011"
  end
  patch do
    url "file://" + TEXWORKS_PATCH_DIR + 'poppler-0003-Add-support-for-persistent-GlobalParams.patch'
    sha256 "fb18b1747f47a608e4b5cd06ab1332df7d12c05e1d1c65526ed2505e07298fd7"
  end
# END TEXWORKS MODIFICATION

  option "with-qt", "Build Qt5 backend"
  option "with-little-cms2", "Use color management system"

  deprecated_option "with-qt4" => "with-qt"
  deprecated_option "with-qt5" => "with-qt"
  deprecated_option "with-lcms2" => "with-little-cms2"

  depends_on "cmake" => :build
  depends_on "pkg-config" => :build
  depends_on "cairo"
  depends_on "fontconfig"
  depends_on "freetype"
  depends_on "gettext"
  depends_on "glib"
  depends_on "jpeg"
  depends_on "libpng"
  depends_on "libtiff"
  depends_on "openjpeg"
  depends_on "qt" => :optional
  depends_on "little-cms2" => :optional

  conflicts_with "pdftohtml", "pdf2image", "xpdf",
    :because => "poppler, pdftohtml, pdf2image, and xpdf install conflicting executables"

  resource "font-data" do
    url "https://poppler.freedesktop.org/poppler-data-0.4.8.tar.gz"
    sha256 "1096a18161f263cccdc6d8a2eb5548c41ff8fcf9a3609243f1b6296abdf72872"
  end

  def install
    ENV.cxx11

    args = std_cmake_args + %W[
      -DENABLE_XPDF_HEADERS=ON
      -DENABLE_GLIB=ON
      -DENABLE_QT5=ON
      -DENABLE_CMS=lcms2
      -DBUILD_GTK_TESTS=OFF
      -DENABLE_UNSTABLE_API_ABI_HEADERS=ON
      -DWITH_GObjectIntrospection=OFF
      -DCMAKE_INSTALL_INCLUDEDIR=#{include}
      -DCMAKE_INSTALL_LIBDIR=#{lib}
    ]

    system "cmake", ".", *args
    system "make", "install"
    resource("font-data").stage do
      system "make", "install", "prefix=#{prefix}"
    end

    libpoppler = (lib/"libpoppler.dylib").readlink
    ["#{lib}/libpoppler-cpp.dylib", "#{lib}/libpoppler-glib.dylib", "#{lib}/libpoppler-qt5.dylib", 
     *Dir["#{bin}/*"]].each do |f|
      macho = MachO.open(f)
      lst=macho.linked_dylibs()
      lst.each do |ln|
        if ln.match(/^@rpath/)
          macho.change_dylib(ln, ln.gsub("@rpath","/usr/local/opt/poppler/lib"))
        end
      end
      macho.write!
    end
  end

  test do
    system "#{bin}/pdfinfo", test_fixtures("test.pdf")
  end
end
