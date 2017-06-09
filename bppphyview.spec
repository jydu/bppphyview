%define _basename bppphyview
%define _version 0.5.0
%define _release 1
%define _prefix /usr

URL: http://biopp.univ-montp2.fr/forge/bppphyview

Name: %{_basename}
Version: %{_version}
Release: %{_release}
License: CECILL-2.0
Vendor: The Bio++ Project
Source: http://biopp.univ-montp2.fr/repos/sources/%{_basename}-%{_version}.tar.gz
Summary: Bio++ Phylogenetic Viewer
Group: Productivity/Scientific/Other

Requires: libbpp-phyl9 = 2.3.0
Requires: libbpp-core2 = 2.3.0
Requires: libbpp-qt1 = 2.3.0
%if 0%{?fedora} || 0%{?rhel_version} || 0%{?centos_version}
Requires: qt >= 4.6.0
%endif
%if 0%{?suse_version}
Requires: libqt4 >= 4.6.0
%endif
%if 0%{?mdkversion}
%ifarch x86_64
Requires: lib64qtgui4 >= 4.6.0
%else
Requires: libqtgui4 >= 4.6.0
%endif
%endif

BuildRoot: %{_builddir}/%{_basename}-root
BuildRequires: cmake >= 2.8.11
BuildRequires: gcc-c++ >= 4.7.0
BuildRequires: groff
BuildRequires: libbpp-core2 = 2.3.0
BuildRequires: libbpp-core-devel = 2.3.0
BuildRequires: libbpp-phyl9 = 2.3.0
BuildRequires: libbpp-phyl-devel = 2.3.0
BuildRequires: libbpp-qt1 = 2.3.0
BuildRequires: libbpp-qt-devel = 2.3.0

%if 0%{?fedora} || 0%{?rhel_version} || 0%{?centos_version}
BuildRequires: qt >= 4.6.0
BuildRequires: qt-devel >= 4.6.0
%endif
%if 0%{?suse_version}
BuildRequires: libqt4 >= 4.6.0
BuildRequires: libqt4-devel >= 4.6.0
%endif
%if 0%{?mdkversion}
%ifarch x86_64
BuildRequires: lib64qtgui4 >= 4.6.0
BuildRequires: lib64qt4-devel >= 4.6.0
%else
BuildRequires: libqtgui4 >= 4.6.0
BuildRequires: libqt4-devel >= 4.6.0
%endif
%endif

AutoReq: yes
AutoProv: yes

%if 0%{?mandriva_version}
%if %{mandriva_version} >= 2011
BuildRequires: xz
%define zipext xz
%else
BuildRequires: lzma
%define zipext lzma
%endif
%else
%if 0%{?distribution:1} && "%{distribution}" == "Mageia"
BuildRequires: xz
%define zipext xz
%else
#For all other distributions:
BuildRequires: gzip
%define zipext gz
%endif
%endif

%description
Bio++ Phylogenetic Viewer, using the Qt library.

%prep
%setup -q

%build
CFLAGS="-I%{_prefix}/include $RPM_OPT_FLAGS"
CMAKE_FLAGS="-DCMAKE_INSTALL_PREFIX=%{_prefix}"
if [ %{_lib} == 'lib64' ] ; then
  CMAKE_FLAGS="$CMAKE_FLAGS -DLIB_SUFFIX=64"
fi
if [ %{zipext} == 'lzma' ] ; then
  CMAKE_FLAGS="$CMAKE_FLAGS -DDOC_COMPRESS=lzma -DDOC_COMPRESS_EXT=lzma"
fi
if [ %{zipext} == 'xz' ] ; then
  CMAKE_FLAGS="$CMAKE_FLAGS -DDOC_COMPRESS=xz -DDOC_COMPRESS_EXT=xz"
fi

cmake $CMAKE_FLAGS .
make

%install
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root)
%doc AUTHORS.txt COPYING.txt INSTALL.txt ChangeLog
%{_prefix}/bin/phyview
%{_prefix}/share/man/man1/phyview.1.%{zipext}

%changelog
* Wed May 10 2017 Julien Dutheil <julien.dutheil@univ-montp2.fr> 0.5.0-1
- Compatibility update with Bio++ 2.3.0.
* Mon Sep 28 2014 Julien Dutheil <julien.dutheil@univ-montp2.fr> 0.4.0-1
- Several bug fixed.
- New clickable panel with list of trees in memory.
- New dialog to insert subtrees.
* Fri Mar 08 2013 Julien Dutheil <julien.dutheil@univ-montp2.fr> 0.3.0-1
- Compatibility update.
- New option for header line in names translation.
* Thu Feb 09 2012 Julien Dutheil <julien.dutheil@univ-montp2.fr> 0.2.1-1
- Compatibility update.
* Thu Jun 09 2011 Julien Dutheil <julien.dutheil@univ-montp2.fr> 0.2.0-1
* Mon Feb 28 2011 Julien Dutheil <julien.dutheil@univ-montp2.fr> 0.1.0-1

