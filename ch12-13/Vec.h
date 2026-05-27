#pragma once
#ifndef GUARD_VEC_H
#define GUARD_VEC_H

#include <memory>
#include <algorithm>
#include <cstddef> //ptrdiff_t

using namespace std;

template <class T> class Vec {
public:
	//속성
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T& reference; //&
	typedef const T& const_reference; //const &

	/*
	Vec<int> grades;
	Vec<int> pass;
	pass = grades;
	1. operator = 필요
	2. Vec() 사본 만든 생성자
	*/

	//생성자 (여러가지)
	//1.빈 객체
	Vec() { create(); };
	//2.백터 크기와 선택적 초기값 정의하기
	explicit Vec(size_type n, const T& val = T()) { create(n, val); };
	//3.사본 만드는 생성자
	Vec(const Vec& v) { create(v.begin(), v.end()); };

	//백터 크기와 인덱스에 관한 새로운 함수들
	size_type size() const { return avail - data; } //수정
	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) const { return data[i]; }

	Vec& operator = (const Vec&);

	//반복자를 반환하는 새로운 함수
	iterator begin() { return data; } 
	const_iterator begin() const { return data; }

	iterator end() { return avail; } //수정
	const_iterator end() const { return avail; } //수정

	//인터페이스(미완성)
	void push_back(const T& val) {
		if (avail == limit) //필요하다면 저장 공간 확보
			grow();

		unchecked_append(val); //새로운 요소 추가
	}

	//Q9을 위해 추가
	void push_back_grow_once(const T& t) {
		grow_once();
		unchecked_append(t);
	}

	//소멸자
	~Vec() { uncreate(); }
	void clear() { uncreate(); };
	bool empty() const { return data == avail; } //0 == 0? True
private:
	iterator data; //vec의 첫번째 요소를 가리키는 포인터
	iterator avail; //vec의 마지막 요소 다음을 가리키는 포인터
	iterator limit; //사용할 수 있는 마지막 요소의 다음을 가치키는 포인터

	allocator<T> alloc; //메모리 할당 위해 관리하는 객체

	//멤버 함수
	//1.생성자: 메모리 할당 + 값 초기화 함수
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);
	//2.소멸자: 메모리 해제
	void uncreate();

	//3.유틸리티 함수들(push_back의 지원 함수)
	void grow();
	void grow_once(); //Q9을 위해 추가
	void unchecked_append(const T&);
};

template <class T> Vec<T>& Vec<T>::operator=(const Vec& rhs) {
	//int i = 0;
	//lhs = left-hand side(i) = 변수
	//rhs = right-hand side(0) = 값
	//자가 할당 여부 확인
	if (&rhs != this) {
		//좌변이 지닌 배열이 점유하는 메모리를 해제
		uncreate();

		//우변이 지닌 요소를 좌변으로 복사
		create(rhs.begin(), rhs.end());
	}
	return *this;
}
template <class T> void Vec<T>::create() {
	data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val) {
	data = alloc.allocate();
	limit = avail = data + n;
	uninitialized_fill(data, limit, val);
}

template <class T>
void Vec<T>::create(const_iterator i, const_iterator j) {
	data = alloc.allocate(j - i);
	limit = avail = uninitialized_copy(i, j, data);
}

template <class T>
void Vec<T>::uncreate() {
	if (data) {
		//역순서대로 모든 요소를 소멸하고 메모리 해제
		iterator it = avail; //마지막 요소 다음에 가리키는 포인터
		while (it != data) //첫 번째 요소를 가리키는 포인터까지
			alloc.destroy(--it);

			//할당한 메모리 공간을 해제 (비우기)
			alloc.deallocate(data, limit - data);
	}
	//모든 포인터를 재저의 (재설정)
	data = limit = avail = 0;
}

template <class T>
void Vec<T>::unchecked_append(const T& val) {
	//'avail' = 할당되지 않은 사용 가능 공간
	alloc.construct(avail++, val);
}

//사용 가능한 공간은 다 채우면
//벡터 크기를 2배로 증가하는 함수
template <class T>
void Vec<T>::grow() {
	size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

	//새로운 공간 할당하고 모든 있는 요소를 복사
	iterator new_data = alloc.allocate(new_size);//할당
	iterator new_avail = uninitialized_copy(data, avail, new_data);

	//구공간을 소멸
	uncreate();

	//모든 포인터를 새로운 공간에서 가리켜
	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}

//Q9을 위해 추가
template <class T>
void Vec<T>::grow_once() {
	size_type new_size = limit - data + ptrdiff_t(1);

	//새로운 공간 할당하고 모든 있는 요소를 복사
	iterator new_data = alloc.allocate(new_size);//할당
	iterator new_avail = uninitialized_copy(data, avail, new_data);

	//구공간을 소멸
	uncreate();

	//모든 포인터를 새로운 공간에서 가리켜
	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}
#endif 
