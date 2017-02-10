#include "ContactListener.h"

void MyContactListener::BeginContact(b2Contact * contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData != nullptr)
	{
		static_cast<DynamicObj*>(bodyUserData)->contactEvent(contact, 1);
		return;
	}

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData != nullptr)
	{
		static_cast<DynamicObj*>(bodyUserData)->contactEvent(contact, 1);
		return;
	}
}

void MyContactListener::EndContact(b2Contact * contact)
{

	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData != nullptr)
	{
		static_cast<DynamicObj*>(bodyUserData)->contactEvent(contact, 0);
		return;
	}

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData != nullptr)
	{
		static_cast<DynamicObj*>(bodyUserData)->contactEvent(contact, 0);
		return;
	}

}
