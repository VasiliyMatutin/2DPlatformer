#include "ContactListener.h"

void MyContactListener::BeginContact(b2Contact * contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData != nullptr && !contact->GetFixtureB()->GetBody()->GetFixtureList()->IsSensor())
	{
		if (contact->GetFixtureA()->GetBody()->GetType() == b2BodyType::b2_staticBody)
		{
			for (int i = 0; i < 2; i++)
			{
				to_destroy_list.push_back(static_cast<NonStaticObj*>(contact->GetFixtureB()->GetBody()->GetUserData()));
			}
		}
		else
		{
			static_cast<ContactObject*>(bodyUserData)->contactEvent(contact, 1);
		}
	}

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData != nullptr && !contact->GetFixtureA()->GetBody()->GetFixtureList()->IsSensor())
	{
		if (contact->GetFixtureB()->GetBody()->GetType() == b2BodyType::b2_staticBody)
		{
			for (int i = 0; i < 2; i++)
			{
				to_destroy_list.push_back(static_cast<NonStaticObj*>(contact->GetFixtureA()->GetBody()->GetUserData()));
			}
		}
		else
		{
			static_cast<ContactObject*>(bodyUserData)->contactEvent(contact, 1);
		}
	}
}

void MyContactListener::EndContact(b2Contact * contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData != nullptr && !contact->GetFixtureB()->GetBody()->GetFixtureList()->IsSensor() && contact->GetFixtureA()->GetBody()->GetType() != b2BodyType::b2_staticBody)
	{
		static_cast<ContactObject*>(bodyUserData)->contactEvent(contact, 0);
	}

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData != nullptr && !contact->GetFixtureA()->GetBody()->GetFixtureList()->IsSensor() && contact->GetFixtureB()->GetBody()->GetType() != b2BodyType::b2_staticBody)
	{
		static_cast<ContactObject*>(bodyUserData)->contactEvent(contact, 0);
	}
}

void MyContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
	if (impulse->normalImpulses[0] > 100) //limit of pressure
	{
		if (contact->GetFixtureA()->GetBody()->GetType() == b2BodyType::b2_dynamicBody)
		{
			to_destroy_list.push_back(static_cast<NonStaticObj*>(contact->GetFixtureA()->GetBody()->GetUserData()));
		}
		else if (contact->GetFixtureB()->GetBody()->GetType() == b2BodyType::b2_dynamicBody)
		{
			to_destroy_list.push_back(static_cast<NonStaticObj*>(contact->GetFixtureB()->GetBody()->GetUserData()));
		}
	}
}

std::list<NonStaticObj*>* MyContactListener::getToDestroyListPtr()
{
	return &to_destroy_list;
}
