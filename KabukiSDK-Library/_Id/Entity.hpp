/** Kabuki Software Development Kit
    @file    /.../KabukiSDK/_Id/Entity.hpp
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2016 [Cale McCollough](calemccollough.github.io)

                            All right reserved (R).

        Licensed under the Apache License, Version 2.0 (the "License"); you may
        not use this file except in compliance with the License. You may obtain
        a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
*/
 
#pragma once

#include "Address.hpp"
#include "EmailAddress.hpp"
#include "Profile.hpp"

namespace _Id {

class _KabukiSDK Entity
/** A entinty with contact information. 
    @todo Attach a compressed image link.
*/
{
    public:

    Entity (const string& aFirstName = "", const string& aLastName = "", const string& anEmailAdress = "", 
        const string& aPrimaryPhoneNum = "", const string& aStreetAdress1 = "", const string& aZipCode1 = "", 
        const string& aStreetAdress2 = "", const string& aZipCode2 = "");
    /*< A real-world enity with . */

    string& getName ();
    /*< Gets the entity's first/only name. */

    void setName (const string& s);
    /*< Attempts to set the fname string to the new string. */

    virtual int search (const string& query);
    /*< Returns true if this entity contains the search query. */
    
    virtual void print (Terminal& slot);
    /*< Prints this object to a terminal. */
    
    private:

    string name,                            //< The legal name of the entity.
        phoneNumber;                        //< The phone number of the entity.
    Address address;                        //< The address of the entity.
    vector<string> tags;                    //< Metadata tags.
    vector<Address> addresses;              //< The address of the entity.
    vector<EmailAddress> emailAddresses;    //< The email address of the entity.
    vector<Profile> profiles;               //< The online profiles this entinty is attached to.
    vector<string> notes;                   //< An array of notes about the enitity.
};

}   //< namespace _Id
