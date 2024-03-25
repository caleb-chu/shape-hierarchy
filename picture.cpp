#include "picture.hpp"
#include <iostream>
#include <utility>
using namespace std;

Picture::Picture()
	:head(nullptr), tail(nullptr)
{
}

Picture::Picture(const Picture& other)
{
	if (other.head == nullptr)
	{
		head = nullptr;
		tail = nullptr;
	}
	else 
	{
		head = new ListNode;
		head->shape = other.head->shape->clone();
		head->next = other.head->next;
		head->prev = other.head->prev;

		ListNode* next = other.head->next;
		ListNode* temp = head;
		while(next != nullptr)
		{
			temp->next = new ListNode;
			temp->next->shape = next->shape->clone();
			temp->next->next = next->next;
			temp->next->prev = next->prev;

			temp = temp->next;
			next = next->next;
		}
		tail = temp;
	}

}

Picture::Picture(Picture&& other)
	:head(other.head), tail(other.tail)
{
	other.head = nullptr;
	other.tail = nullptr;
}

void Picture::swap(Picture& other)
{
	ListNode* h = head;
	ListNode* t = tail;

	head = other.head;
	tail = other.tail;

	other.head = h;
	other.tail = t;

	h = nullptr;
	t = nullptr;
}

Picture &Picture::operator=(const Picture& other)
{
	if (&other  == this)
		return *this;
	else
	{
		Picture pic(other);
		swap(pic);
		return *this;
	}
}

Picture &Picture::operator=(Picture &&other)
{
	swap(other);
	return *this;
}

void Picture::add(const Shape& shape)
{
	ListNode* newNode = new ListNode;
	newNode->shape = shape.clone();
	newNode->next = head;
	newNode->prev = nullptr;
	if (head)
	{
		head->prev = newNode;
		head = newNode;
	}
	head = newNode;

	if (tail == nullptr)
		tail = newNode;
}

void Picture::print_all(ostream& out) const
{
	for(ListNode *current = tail; current != nullptr; current = current->prev)
	{
		current->shape->print(out);
		current->shape->draw(out);
	}
}

void Picture::draw_all(ostream& out) const
{
	for (ListNode *current = tail; current != nullptr; current = current->prev)
	{
		current->shape->draw(out);
	}
}

double Picture::total_area() const
{
	double count{0.0};
	ListNode *current = head;
	for(; current != nullptr; current = current->next)
	{
		count += current->shape->area();
	}
	return count;
}

Picture::~Picture()
{
	ListNode *current = head;
	while (current != nullptr)
	{
		ListNode* temp = current;
		delete current->shape;
		current = current->next;
		delete temp;
	}
}
