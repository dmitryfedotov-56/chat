	#pragma once
	/***********************************************************/
	/*                  Chat Classes Definition                */
	/***********************************************************/

	#include <string.h>
	#include <stdlib.h>
	#include "chat_access.h"
	#include "chat_object.h"

	/***********************************************************/
	/*                      Chat Definition                    */
	/***********************************************************/

	class Chat : public Chat_Access {
	public:

		virtual Session_Access* create_User(const char* name, const char* password);
		
		virtual Session_Access* start_Session(const char* name, const char* password);
		
		virtual ID new_User(const char* name, const char* password);

		virtual ID user_ID(const char* name);		// try to find user ID

		virtual ID find_ID(const char* name);		// find user ID, error if not found

		virtual void open_Chat(ID user_list_id);	// open chat

		virtual void close_Chat();					// close chat

		ID user_list_id;
		User_Access* user ;
		List_Access* user_list ;
	};

	/***********************************************************/
	/*                      Session Definition                 */
	/***********************************************************/

	class Chat;

	class Session : public Session_Access {
		friend class Message_Collection;
	public:

		virtual const char* user_Name() const;

		virtual void send_Message(const char* recipient, const char* text);

		virtual void broadcast_Message(const char* text);

		virtual Message_Collection_Access* select_Messages(const Condition* condition, 
			Order order);

		virtual void change_Password(const char* password);

		virtual void open();

		Session(Chat* chat, ID user_id);

		virtual ~Session();

	private:

		virtual void to_User_List(ID message_id);				// to user list

		virtual void to_Peer_List(ID message_id, ID peer_id);	// to peer list
/*
			user data
*/
		ID user_id = NOTANID;
		ID list_id = NOTANID;
		const char* user_name = nullptr;
/*
			access objects
*/
		Chat* chat = nullptr;
		User_Access* user = nullptr;
		User_Access* peer = nullptr;
		Message_Access* message = nullptr;
		Message_Link_Access* message_link;
		List_Access* message_link_list = nullptr;
	};

	/***********************************************************/
	/*              Message Collection Implementation          */
	/***********************************************************/

	class Message_Collection : public Message_Collection_Access {
	public:
/*
		abstract class methods
*/
		virtual bool has_Next();

		virtual const char* message_Text() const ;
		virtual const time_t message_Time() const;
		virtual bool message_Sent() const;
		virtual bool message_Received() const;
		virtual const char* sender_Name() const;
		virtual const char* recipient_Name() const ;
		virtual ID message_ID() const;
/*
		implementation methods
*/
		Message_Collection(Session* session, 
			ID list_id, 
			const Condition* condition, 
			Order order);

		~Message_Collection();

		virtual void open();		// open collectin object

		virtual void open_Message(ID message_link_id);	// open message

		virtual bool suitable_Message();				// suitable

		ID get_Init();									// get initial message

		ID get_Next();									// get next mesage

		void clear();									// clear data

		const char* get_Name(const char* name, ID id) const;
	
	private:
/*
			iterator data block
*/
		Session_Access* session = nullptr;
		Order order = Order::direct;
		bool started = false;
		const Condition* condition = nullptr;
		ID list_id = NOTANID;
		unsigned counter = 0;
/*
			message data
*/
		time_t time = 0;
		bool sent = false;
		bool received = false;

		ID message_id = NOTANID;
		ID sender_id = NOTANID;
		ID recipient_id = NOTANID;

		const char* text = nullptr;				// allocatable
		const char* peer_name = nullptr;		// allocatable
/*
			access objects 
*/
		List_Access* message_link_list = nullptr;
		User_Access* peer = nullptr;
		Message_Link_Access* message_link = nullptr;
		Message_Access* message = nullptr;
	};

	/***********************************************************/


