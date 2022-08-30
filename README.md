# C-Extension Module

https://devocean.sk.com/experts/techBoardDetail.do?ID=163718&page=2&searchData=Programming+Language&subIndex=&idList=%5B164130%2C+164070%2C+163937%2C+163932%2C+163853%2C+163848%2C+163835%2C+163718%2C+163675%2C+163669%2C+163649%2C+163631%5D

C -> Python

이때 .pyd는 Python C-API를 사용하여 작성된 확장 모듈이미 컴파일된 상태의 파일이다.

## 핵심요소

- PyObject : Python에서 사용(한/될) 객체타입
  - Py_DECREF : PyObject 생성시 ref count = 1이 되고 이를 -1시키는 함수
  - Py_INCREF : 위에와 달리 다른 ref가 추가시 +1시키는 함수 / ex) return PyObj
- PyMethodDef : 해당 모듈에 포함될 Method 명시
  - 이때 매개변수를 받을 방법으로 METH_VARARGS는 PyObject self, PyObject args 두개를 전달 받음
- PyModuleDef : PyModule_Create로 전달될 구조체 정의
  - PyModuleDef_HEAD_INIT, 모듈명, 모듈docs, GIL, PyMethodDEf(Method Array)
- PyMODINT_FUNC
  - PyModule_Create(&PyModuleDef)

## Compile

distutils.core를 이용하여 위의 파일을 컴파일한다.
이때 자동으로 해당 Python env의 lib에 배치되어 모듈명으로 import한다.
