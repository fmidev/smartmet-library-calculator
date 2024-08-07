%bcond_with tests
%define DIRNAME calculator
%define LIBNAME smartmet-%{DIRNAME}
%define SPECNAME smartmet-library-%{DIRNAME}
%define DEVELNAME %{SPECNAME}-devel
Summary: Querydata calculator
Name: %{SPECNAME}
Version: 24.7.12
Release: 1%{?dist}.fmi
License: MIT
Group: Development/Libraries
URL: https://github.com/fmidev/smartmet-library-calculator
Source0: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

%if 0%{?rhel} && 0%{rhel} < 9
%define smartmet_boost boost169
%else
%define smartmet_boost boost
%endif

BuildRequires: rpm-build
BuildRequires: gcc-c++
BuildRequires: make
BuildRequires: %{smartmet_boost}-devel
BuildRequires: smartmet-library-newbase-devel >= 24.8.7
BuildRequires: smartmet-library-macgyver-devel >= 24.8.7
BuildRequires: smartmet-library-gis-devel >= 24.8.7
BuildRequires: freetype-devel
%if %{with tests}
BuildRequires: smartmet-library-regression
%endif
Requires: smartmet-library-newbase >= 24.8.7
#TestRequires: make
#TestRequires: gcc-c++
#TestRequires: smartmet-library-regression
#TestRequires: smartmet-library-macgyver-devel
#TestRequires: smartmet-library-newbase-devel >= 24.8.7
#TestRequires: smartmet-library-gis-devel >= 24.8.7
#TestRequires: %{smartmet_boost}-devel
#TestRequires: smartmet-timezones
Provides: %{LIBNAME}

%description
Querydata calculator library

%prep
rm -rf $RPM_BUILD_ROOT

%setup -q -n %{SPECNAME}
 
%build
make %{_smp_mflags}
%if %{with tests}
make test %{_smp_mflags}
%endif

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
Requires: %{SPECNAME} = %{version}-%{release}
Requires: smartmet-library-macgyver-devel

%description -n %{DEVELNAME}
%{DIRNAME} development files

%files -n %{DEVELNAME}
%defattr(0664,root,root,-)
%{_includedir}/smartmet/%{DIRNAME}/*.h

%changelog
* Fri Jul 12 2024 Andris Pavēnis <andris.pavenis@fmi.fi> 24.7.12-1.fmi
- Replace many boost library types with C++ standard library ones

* Thu May 16 2024 Andris Pavēnis <andris.pavenis@fmi.fi> 24.5.16-1.fmi
- Clean up boost date-time uses

* Mon May  6 2024 Andris Pavēnis <andris.pavenis@fmi.fi> 24.5.6-1.fmi
- Use Date library (https://github.com/HowardHinnant/date) instead of boost date_time

* Fri Feb 23 2024 Mika Heiskanen <mika.heiskanen@fmi.fi> 24.2.23-1.fmi
- Full repackaging

* Tue Jan 30 2024 Mika Heiskanen <mika.heiskanen@fmi.fi> 24.1.30-1.fmi
- Repackaged due to newbase ABI changes

* Thu Nov 16 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.11.16-1.fmi
- Repackage due to incorrect version value update in one of previous commits

* Fri Jul 28 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.7.28-1.fmi
- Repackage due to bulk ABI changes in macgyver/newbase/spine

* Mon Jul 10 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.7.10-1.fmi
- Use postgresql 15, gdal 3.5, geos 3.11 and proj-9.0

* Thu Jun 16 2022 Andris Pavēnis <andris.pavenis@fmi.fi> 22.6.16-1.fmi
- Add support of HEL9, upgrade to libpqxx-7.7.0 (rhel8+) and fmt-8.1.1

* Tue May 24 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.5.24-1.fmi
- Repackaged due to NFmiArea ABI changes

* Fri May 20 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.5.20-1.fmi
- Repackaged due to ABI changes to newbase LatLon methods

* Wed Oct  6 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.10.6-1.fmi
- Used clang-tidy to modernize code

* Thu May  6 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.5.6-1.fmi
- Repackaged due to ABI changes in NFmiAzimuthalArea

* Thu Feb 18 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.2.18-1.fmi
- Repackaged due to NFmiArea ABI changes

* Tue Feb 16 2021 Andris Pavēnis <andris.pavenis@fmi.fi> - 21.2.16-1.fmi
- Repackaged due to newbase ABI changes

* Mon Feb 15 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.2.15-1.fmi
- Repackaged due to newbase ABI changes

* Thu Jan 14 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.1.14-1.fmi
- Repackaged smartmet to resolve debuginfo issues

* Wed Oct  7 2020 Andris Pavenis <andris.pavenis@fmi.fi> - 20.10.7-1.fmi
- Build update: use makefile.inc from smartmet-library-macgyver
- Fail build in case of unresolved references in built library

* Thu Aug 27 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.27-1.fmi
- NFmiGrid API changed

* Wed Aug 26 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.26-1.fmi
- Numerous newbase API changes

* Tue Aug 25 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.25-1.fmi
- Repackaged due to NFmiGrid API change

* Fri Aug 21 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.21-1.fmi
- Upgrade to fmt 6.2

* Fri Jul 31 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.7.31-1.fmi
- Repackaged due to libpqxx upgrade

* Wed Jul  1 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.7.1-1.fmi
- Repackaged

* Fri Apr 24 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.4.24-1.fmi
- Repackaged
* Sat Apr 18 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.4.18-1.fmi
- Upgrade to Boost 1.69

* Thu Apr  2 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.4.2-1.fmi
- Repackaged due to newbase API changes

* Thu Mar 26 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.3.26-1.fmi
- NFmiArea API changed

* Thu Feb  6 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.2.6-1.fmi
- NFmiPoint ABI changed: Z-coordinate removed

* Wed Jan  8 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.1.8-1.fmi
- NFmiPoint ABI changed

* Fri Dec 13 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.12.13-1.fmi
- Removed obsolete GDAL include path settings

* Wed Dec  4 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.12.4-1.fmi
- Use -fno-omit-frame-pointer for a better profiling and debugging experience

* Tue Dec 3 2019 Anssi Reponen <anssi.reponen@fmi.fi> - 19.12.3-1.fmi
- Two new functions added for checking missing parameter values (BRAINSTORM-1727)

* Wed Nov 20 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.11.20-1.fmi
- Repackaged due to newbase API changes

* Tue Nov 5 2019 Anssi Reponen <anssi.reponen@fmi.fi> - 19.11.5-1.fmi
- Use parameter mapping if it has been defined in configuration file (BRAINSTORM-1719)

* Thu Oct 31 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.10.31-1.fmi
- Rebuilt due to newbase API/ABI changes

* Thu Sep 26 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.9.26-1.fmi
- Added ASAN and TSAN builds
- Repackaged due to newbase ABI changes

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
