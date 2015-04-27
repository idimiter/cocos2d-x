/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "base/CCEventListenerOrientation.h"
#include "base/CCEventOrientation.h"

NS_CC_BEGIN

const std::string EventListenerOrientation::LISTENER_ID = "__cc_orientation";

EventListenerOrientation::EventListenerOrientation()
{

}

EventListenerOrientation::~EventListenerOrientation()
{
    CCLOGINFO("In the destructor of OrientationEventListener. %p", this);
}

EventListenerOrientation* EventListenerOrientation::create(const std::function<void(Orientation, Event*)>& callback)
{
    EventListenerOrientation* ret = new (std::nothrow) EventListenerOrientation();
    if (ret && ret->init(callback))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

bool EventListenerOrientation::init(const std::function<void(Orientation, Event* event)>& callback)
{
    auto listener = [this](Event* event){
        auto dirEvent = static_cast<EventOrientation*>(event);
        this->onOrientationEvent(dirEvent->_direction, event);
    };
    
    if (EventListener::init(Type::ORIENTATION, LISTENER_ID, listener))
    {
        onOrientationEvent = callback;
        return true;
    }
    
    return false;
}

EventListenerOrientation* EventListenerOrientation::clone()
{
    auto ret = new (std::nothrow) EventListenerOrientation();
    
    if (ret && ret->init(onOrientationEvent))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

bool EventListenerOrientation::checkAvailable()
{
    CCASSERT(onOrientationEvent, "");
    
    return true;
}

NS_CC_END
