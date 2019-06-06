%define DIRNAME calculator
%define LIBNAME smartmet-%{DIRNAME}
%define SPECNAME smartmet-library-%{DIRNAME}
%define DEVELNAME %{SPECNAME}-devel
Summary: Querydata calculator
Name: %{SPECNAME}
Version: 18.11.24
Release: 1%{?dist}.fmi
License: MIT
Group: Development/Libraries
URL: https://github.com/fmidev/smartmet-library-calculator
Source0: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: rpm-build
BuildRequires: gcc-c++
BuildRequires: make
BuildRequires: boost-devel
BuildRequires: smartmet-library-newbase-devel >= 18.10.23
BuildRequires: smartmet-library-macgyver-devel >= 18.11.24
BuildRequires: freetype-devel
BuildRequires: gsl
Requires: smartmet-library-newbase >= 18.10.23
Provides: %{LIBNAME}

%description
Querydata calculator library

%prep
rm -rf $RPM_BUILD_ROOT

%setup -q -n %{SPECNAME}
 
%build
make %{_smp_mflags}

%install
%makeinstall

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,0775)
%{_libdir}/lib%{LIBNAME}.so

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%package -n %{DEVELNAME}
Summary: FMI %{DIRNAME} development files
Provides: %{DEVELNAME}
Requires: %{SPECNAME}

%description -n %{DEVELNAME}
%{DIRNAME} development files

%files -n %{DEVELNAME}
%defattr(0664,root,root,-)
%{_includedir}/smartmet/%{DIRNAME}/*.h

%changelog
* Sat Nov 24 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.11.24-1.fmi
- Fixed a memory leak in PercentageCalculator

* Mon Oct  1 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.10.1-1.fmi
- Added option -g to get a proper debuginfo package

* Sun Sep 16 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.9.16-2.fmi
- Silenced CodeChecker warnings

* Sun Sep 16 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.9.16-1.fmi
- Silenced CodeChecker warnings

* Sat Sep  8 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.9.8-1.fmi
- Silenced CodeChecker warnings

* Wed Aug  1 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.8.1-1.fmi
- Use C++11 for-loops instead of BOOST_FOREACH

* Wed Jul 25 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.7.25-1.fmi
- Prefer nullptr over NULL

* Mon Jul 23 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.7.23-1.fmi
- Silenced CodeChecker warnings

* Wed Jun 20 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.6.20-1.fmi
- Use an atomic counter instead of mutexes

* Wed May  2 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.5.2-1.fmi
- Repackaged since newbase NFmiEnumConverter ABI changed

* Sat Apr  7 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.4.7-1.fmi
- Upgrade to boost 1.66

* Mon Aug 28 2017 Mika Heiskanen <mika.heiskanen@fmi.fi> - 17.8.28-1.fmi
- Upgrade to boost 1.65

* Tue Aug 22 2017 Mika Heiskanen <mika.heiskanen@fmi.fi> - 17.8.22-1.fmi
- Added handling of timezones names "local" and "localtime"
- Changed default timezone to be UTC, Europe/Helsinki is not portable

* Thu Mar 16 2017 Mika Heiskanen <mika.heiskanen@fmi.fi> - 17.3.16-1.fmi
- Removed use of deprecated macgyver Cast.h

* Fri Feb 10 2017 Mika Heiskanen <mika.heiskanen@fmi.fi> - 17.2.10-1.fmi
- Recompiled due to newbase API changes

* Fri Jan 27 2017 Mika Heiskanen <mika.heiskanen@fmi.fi> - 17.1.27-1.fmi
- Recompiled due to NFmiQueryData object size change

* Thu Jan 12 2017 Mika Heiskanen <mika.heiskanen@fmi.fi> - 17.1.12-1.fmi
- First version extracted from the full text generator library
