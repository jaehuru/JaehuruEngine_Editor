# Description
이 프로젝트는 게임 엔진의 본질을 이해하고 3D 그래픽 렌더링 기술을 깊이 있게 탐구하기 위해 시작되었습니다.
Win32 API를 활용한 윈도우 창 생성 및 메시지 루프 처리와 같은 저수준 시스템부터, DirectX 11을 기반으로 한 렌더링 파이프라인의 직접 구현까지 전 과정을 경험하는 것을 목표로 합니다.
엔진 코어, 게임 툴 에디터, 게임 클라이언트를 명확히 분리하여 엔진 코어를 모듈화함으로써, 유지보수성과 확장성을 고려한 아키텍처 설계를 지향합니다.

## Development Environment
- ' Window OS '
- ' Visual Studio 2022 '

# ⚠️ Caution

## vcpkg 라이브러리 관리 안내 

이 엔진은 [vcpkg](https://github.com/microsoft/vcpkg)를 사용하여 외부 라이브러리를 관리합니다.

- vcpkg가 시스템에 설치되어 있고, `vcpkg integrate install` 명령으로 Visual Studio와 연동되어 있어야 합니다.
- 프로젝트 루트에 있는 `vcpkg.json` 파일에 필요한 라이브러리 목록이 명시되어 있습니다.
- 다음 명령어로 필요한 라이브러리를 한 번에 설치할 수 있습니다. (엔진 루트 폴더에서 터미널/PowerShell을 열고 실행)
```powershell
vcpkg install
```

# 참고한 오픈소스

본 프로젝트는 다음 오픈소스를 참고하여 개발되었습니다.

- [YamYam_Engine](https://github.com/eazuooz/YamYam_Engine) (MIT License)  
  일부 구조와 아이디어, 코드를 기반으로 수정 및 확장하여 사용하였습니다.

해당 프로젝트는 MIT 라이선스를 따르며, 원 저작자의 저작권 및 라이선스 정보는 아래와 같습니다:

> 저작권 (MIT License)  
> Copyright (c) 2023  
>  
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:  
>  
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.  
>  
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
