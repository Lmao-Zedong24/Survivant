#include <iostream>

#include "SurvivantTest/EventManager.h"

int main()
{
	//std::cout << "Hello World" << std::endl;
	//return 0;

	using namespace Core;
	using HelloWorldEvent = Event<>;
	using ligma = Event<int, int>;


	EventManager em;

	HelloWorldEvent::EventDelegate printHW = []() { std::cout << "Hello world" << std::endl; };
	ligma::EventDelegate printLig = [](int i, int j) { std::cout << "Ligma "<< i+j<< std::endl; };

	std::shared_ptr<HelloWorldEvent> hwEvent = std::make_shared<HelloWorldEvent>();
	hwEvent->AddListener(printHW);

	std::shared_ptr<ligma> ligEvent = std::make_shared<ligma>();
	ligEvent->AddListener(printLig);


	em.AddEvent<HelloWorldEvent>(hwEvent);
	em.AddEvent<ligma>(ligEvent);
	em.Invoke<HelloWorldEvent>();

	//ligEvent->Invoke(9, 10);
	em.Invoke<ligma>(9, 10);
}

