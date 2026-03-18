#pragma once
#include <iostream>
#include <string>

class Item //아이템 클래스를 만들어
{
private: //아이템 클래스의 멤버변수는 이름과 가격이야
	std::string name; //멤버변수 초기화
	int price;

public:
	Item() : //아이템 기본생성자 오버로딩(?) 이유?
		name("")
		, price(0)
	{
	}
	Item(const std::string& name, int price) ://const ~& -> 값을 매번 복사하는건 메모리 낭비니까 주소만 주라. 값은 절대 안바꿀거니까 걱정하지말고
		name(name),
		price(price)
	{
	}

	//std::string Getname() const {return name;} //이 함수의 용도? 읽기 전용이라는 거는 아는데, 메인함수에서 활용은?
	//int Getprice(){return price;}

	void PrintInFo()
	{
		std::cout << "[이름: " << name << ", 가격: " << price << "G]" << std::endl;
	}

	void Clear() // size_만 줄이는것 -> removelastitem() 함수를 호출하면 칸은 줄어들지만 입력했던 아이템과 가격은 남아있어 메모리릭 발생,
		// 호텔방 청소라 생각
	{
		name = "";   // 이름을 빈 문자열로 바꿈
		price = 0;   // 가격을 0으로 바꿈
	}
};

template <typename T>
class Inventory
{
private:
	T* pItems_;
	int capacity_;
	int size_;

public:
	Inventory(int capacity = 10) : //초기화리스트
		capacity_(capacity), //멤버 변수capacity_를 capacity로 초기화
		size_(0) //멤버변수 size_를 0으로 초기화? -> 생성되자마자 아이템개수 는 0개가 맞지
	{
		if (capacity_ < 0)
		{
			capacity_ = 1;
		}

		pItems_ = new T[capacity_]; //힙메모리에 할당받음(new)
		//컴퓨터야, 나 Item객체를 capacity에 10개 들어갈 만큼 메모리좀 주라
		//pItems_는 배열[capacity_]의 시작주소만 가지고 있어. 배열 10개 그 자체가 아니야

	}
	~Inventory()
	{
		delete[] pItems_;
		pItems_ = nullptr;
		//std::cout << "인벤토리 클래스 소멸" << std::endl;
	}

	void Additem(const T& item)

	{
		if (size_ < capacity_) //인벤토리에 자리가 있으면,
		{
			pItems_[size_] = item;// 현재 size_(현재 인덱스)에 아이템을 넣는다.
			// pItems_는 new <Item>[capacity]
			size_++;			  // 다음에 올 아이템을 위해 size- +1
		}
		else
		{
			std::cout << "Inventory is Full!!" << std::endl; //인벤토리에 자리가 없으면
		}
	}

	void RemoveLastItem() //아이템
	{
		if (size_ <= 0)
		{
			std::cout << "인벤토리가 비어있습니다." << std::endl;
		}

		std::cout << "마지막 아이템을 제거합니다..." << std::endl;
		--size_;
		pItems_[size_ - 1].Clear();
	}

	int GetSize() const
	{
		return size_;
	}

	int Getcapacity() const
	{
		return capacity_;
	}

	void PrintAllItems() const
	{
		if (size_ == 0)
		{
			std::cout << "인벤토리가 비어있습니다!" << std::endl;
			return;
		}
		std::cout << "아이템 목록: " << std::endl;
		for (int i = 0; i < size_; i++)
		{
			pItems_[i].PrintInFo();
		}

	}

};

int main(void)
{
	Inventory<Item>* MyInventory = new Inventory<Item>();
	//여기서 사용한 T는 T* pItems_, pItems_ = new T[capacity_];

	std::cout << "------- 인벤토리 -------" << std::endl;
	MyInventory->Additem(Item("Dragon Sword", 1500)); //객체가 포인터면 ->
	MyInventory->Additem(Item("HP Potion", 300));
	MyInventory->Additem(Item("MP Potion", 300));
	MyInventory->Additem(Item("Iron Arrow", 500));

	MyInventory->PrintAllItems();
	std::cout << "현재 장비 개수: " << MyInventory->GetSize() << std::endl;
	std::cout << "Max 인벤토리: " << MyInventory->Getcapacity() << std::endl;;
	std::cout << "________________________" << std::endl;

	MyInventory->RemoveLastItem();
	std::cout << "현재 장비 개수: " << MyInventory->GetSize() << std::endl;

	// std::cout << "아이템: " << Item::std::string Getname() const;
	// std::cout << "아이템: " << Item::int GetSize_() ;

	delete MyInventory;
	MyInventory = nullptr;

	return 0;
}