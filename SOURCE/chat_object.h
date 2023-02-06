	#pragma once
	/***********************************************************/
	/*                    Chat Object Access                   */
	/***********************************************************/

	#include <time.h>

	#define ID			size_t			// object ID
	#define NOTANID		SIZE_MAX		// reserved ID

	class Object_Block {
	public:
		virtual void open(ID id) = 0;
		virtual void save() = 0;
		virtual ID create() = 0;
	};

	/***********************************************************/

	class Object_Class { 
	public:
		virtual void open(ID id);				// open object

		virtual void save();					// save object

		Object_Class(Object_Block* block);

	protected:
		Object_Block* object_block = nullptr;
	};

	/***********************************************************/
	/*                     Object List Access                  */
	/***********************************************************/

	class List_Access : public Object_Class {
	public:

		virtual ID create() = 0;	// create list object

		virtual ID init_Element() = 0;
/*
			init list element, returns NOTANID if the list is empty
*/
		virtual ID last_Element() = 0;
/*
			last list element, returns NOTANID if the list is empty
*/
		virtual ID next_Element() = 0;
/*
			next list element, can return NOTANID
*/
		virtual ID prev_Element() = 0;
/*
			previous list element, can return NOTANID
*/
		virtual void include_Element(ID element) = 0;
/*
			include element to the beginning
*/
		// virtual void exclude_Element(ID element) = 0;
/*
			exclude element from the list
*/
		List_Access(Object_Block* block);
	};

	/***********************************************************/

	class User_Access : public Object_Class {
	public:
		virtual ID create(const char* name, const char* pass) = 0;	// create a user

		virtual const char* allocate_Name() const = 0;			// user name
		virtual const char* allocate_Password() const = 0;		// user password
		virtual ID message_Link_List() const = 0;				// message link list ID

		virtual void change_Password(const char* pass) = 0;	// change password
		
		User_Access(Object_Block* block);
	};

	/***********************************************************/

	class Message_Link_Access : public Object_Class {
	public:
		virtual ID create(bool sent, bool received, ID message_id) = 0;	// create a link

		virtual bool message_Sent() const = 0;				// message is sent
		virtual bool message_Received() const = 0;			// message is received
		virtual ID message_ID() const = 0;					// message ID

		Message_Link_Access(Object_Block* block);
	};

	/***********************************************************/

	class Message_Access : public Object_Class {
	public:
		virtual ID create(const char* text, ID sender_id, ID recipient_id) = 0; // create

		virtual const char* allocate_Text() const = 0;		// message text
		virtual time_t message_Time() const = 0;			// message timestamp
		virtual ID sender_ID() const = 0;					// message sender ID
		virtual ID recipient_ID()const = 0;					// message recipient ID
		
		Message_Access(Object_Block* block);
	};

	/***********************************************************/

	class Chat_Class_Access {
	public:
		virtual User_Access* create_User_Access() = 0;
		virtual Message_Access* create_Message_Access() = 0;
		virtual Message_Link_Access* create_Message_Link_Access() = 0;
		virtual List_Access* create_List_Access() = 0;
		virtual ID user_List_ID() = 0;
		virtual void close_Chat_Class() = 0;
	};

	Chat_Class_Access* get_Chat_Class();

	/***********************************************************/

	


