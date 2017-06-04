#include "StrongPlayer.h"

StrongPlayer::StrongPlayer(int _level_width, int _level_height, b2Body * _body, Object * _object, int _health, ReturnEvents* _re) : Player (_level_width,_level_height,_body,_object,_health, _re),
	is_joint_set(0)
{
	max_frame = 8;
	fixed_speed = 2;
	right_row = 3;
	left_row = 1;
	jump_strenght  = 3;
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = STRONG_PLAYER;
	filter.maskBits = MASK_PLAYER;
	body->GetFixtureList()->SetFilterData(filter);
	body->GetFixtureList()->SetDensity(2.5f);
	body->ResetMassData();
	Player::playerUI.setPlayerName("Player2");
	Player::playerUI.setPlayerType("\"The Rock\"");
}

void StrongPlayer::tryToPickupBox()
{
	if (!is_joint_set)
	{
		for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
		{
			b2Fixture* b = edge->contact->GetFixtureB();
			if (b->GetBody()->GetType() == b2BodyType::b2_dynamicBody && b->GetBody()->GetUserData() != nullptr && static_cast<NonStaticObj*>(b->GetBody()->GetUserData())->whoAmI() == ObjectType::BOX && b->GetBody()->GetMass() / 5 < body->GetMass())
			{
				b2WeldJointDef weldJointDef;
				b2Vec2 pos = b->GetBody()->GetPosition();
				weldJointDef.bodyA = body;
				weldJointDef.bodyB = b->GetBody();
				b->GetBody()->SetTransform(pos, 0);
				if (pos.y < body->GetPosition().y)
				{
					continue;
				}

				if (pos.x > body->GetPosition().x)
				{
					weldJointDef.localAnchorA = b2Vec2(object->width / 2 / PIXEL_PER_METER, 0);
					weldJointDef.localAnchorB = b2Vec2(-static_cast<NonStaticObj*>(b->GetBody()->GetUserData())->getObject()->width / 2 / PIXEL_PER_METER, 0);
				}
				else if (pos.x < body->GetPosition().x)
				{
					weldJointDef.localAnchorA = b2Vec2(-object->width / 2 / PIXEL_PER_METER, 0);
					weldJointDef.localAnchorB = b2Vec2(static_cast<NonStaticObj*>(b->GetBody()->GetUserData())->getObject()->width / 2 / PIXEL_PER_METER, 0);
				}
				else
				{
					continue;
				}
				joint = b->GetBody()->GetWorld()->CreateJoint(&weldJointDef);
				box = b->GetBody();
				is_joint_set = true; 
				box_coef = b->GetBody()->GetWorld()->GetGravity().y * b->GetBody()->GetMass() / 40;
				return;
			}
		}
	}
	else
	{
		body->GetWorld()->DestroyJoint(joint);
		is_joint_set = false;
	}
}

void StrongPlayer::throwBox(double x, double y)
{
	if (is_joint_set && (x / PIXEL_PER_METER-box->GetPosition().x)*(box->GetPosition().x- body->GetPosition().x) > 0)
	{
		body->GetWorld()->DestroyJoint(joint);
		is_joint_set = false;
		b2Vec2 direction(x/PIXEL_PER_METER - body->GetPosition().x, y/PIXEL_PER_METER - body->GetPosition().y);
		direction.Normalize();
		box->ApplyLinearImpulseToCenter(b2Vec2(100 * direction.x, 100 * direction.y), 1);
	}
}

void StrongPlayer::update()
{
	if (is_valid)
	{
		if (body->GetJointList()->next != nullptr)
		{
			if (joint->GetReactionForce(1).y < -box_coef || abs(body->GetLinearVelocity().y) > 0.2)
			{
				body->GetWorld()->DestroyJoint(joint);
				is_joint_set = false;
			}
		}
		else
		{
			is_joint_set = false;
		}
		Player::update();
	}
}
