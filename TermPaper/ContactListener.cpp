#include "ContactListener.h"

void MyContactListener::BeginContact(b2Contact * contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData != nullptr && !contact->GetFixtureB()->GetBody()->GetFixtureList()->IsSensor())
	{
		static_cast<ContactObject*>(bodyUserData)->contactEvent(contact, 1);
	}

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData != nullptr && !contact->GetFixtureA()->GetBody()->GetFixtureList()->IsSensor())
	{
		static_cast<ContactObject*>(bodyUserData)->contactEvent(contact, 1);
	}
}

void MyContactListener::EndContact(b2Contact * contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData != nullptr && !contact->GetFixtureB()->GetBody()->GetFixtureList()->IsSensor())
	{
		static_cast<ContactObject*>(bodyUserData)->contactEvent(contact, 0);
	}

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData != nullptr && !contact->GetFixtureA()->GetBody()->GetFixtureList()->IsSensor())
	{
		static_cast<ContactObject*>(bodyUserData)->contactEvent(contact, 0);
	}
}
