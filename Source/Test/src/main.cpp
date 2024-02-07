#include <iostream>

#include "SurvivantTest/EventManager.h"
#include "SurvivantTest/InputManager.h"


std::tuple<int, int> func(int i) 
{ 
	return { i, 10 }; 
}


int main()
{
	//std::cout << "Hello World" << std::endl;
	//return 0;

	using namespace Core;
	using namespace App;
	using HelloWorldEvent = Event<>;
	using ligma = Event<int, int>;


	EventManager& em = EventManager::GetInstance();
	InputManager& im = InputManager::GetInstance();

	HelloWorldEvent::EventDelegate printHW = []() { std::cout << "Hello world" << std::endl; };
	ligma::EventDelegate printLig = [](int i, int j) { std::cout << "Ligma "<< i+j<< std::endl; };

	std::shared_ptr<HelloWorldEvent> hwEvent = std::make_shared<HelloWorldEvent>();
	hwEvent->AddListener(printHW);

	std::shared_ptr<ligma> ligEvent = std::make_shared<ligma>();
	ligEvent->AddListener(printLig);


	em.AddEvent<HelloWorldEvent>(hwEvent);
	em.AddEvent<ligma>(ligEvent);
	em.Invoke<HelloWorldEvent>();

	ligEvent->Invoke(8, 9);
	em.Invoke<ligma>(9, 10);

	InputManager::KeyboardKeyType a(1, 1, 1);
	InputManager::KeyCallback aF = [](int i) { std::cout << "Test A: " << i << std::endl; };

	im.AddInputBinding(a, aF);
	im.CallInput(a);

	InputManager::KeyboardKeyType b(1, 2, 3);

	//struct bFunc
	//{
	//	std::tuple<int, int> func(int i) { return { i, 10 }; }
	//};
	
	im.AddInputEventBinding<ligma>(b, &func);
	im.CallInput(b);

}

