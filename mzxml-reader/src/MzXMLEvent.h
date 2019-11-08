#ifndef MzXML_Event_H
#define MzXML_Event_H

namespace MzXML {
    enum EventType {
        PARENT_FILE_EVENT,
        INSTRUMENT_EVENT,
        DATAPROCESSING_EVENT,
        SOFTWARE_EVENT,
        MzXML_ION_EVENT
    };
    class Event {
        private:
        EventType eventType;
        void* payload;
        public:
        Event(EventType eventType, void* payload) {
            this->eventType = eventType;
            this->payload = payload;
        }

        EventType getEventType() const { return this->eventType;}
        const void* getPayload() const { return this->payload;}

    };
}
#endif