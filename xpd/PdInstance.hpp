/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef Z_PD_INSTANCE_HPP
#define Z_PD_INSTANCE_HPP

#include "PdEnvironment.hpp"

namespace xpd
{
    class Patch;
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    //! @brief The Pure Data instance.
    //! @details The Instance is a wrapper for the Pure Data's native instance.
    //! With the default constructor, the Instance won't be initialized. The Instance has some
    //! kind of smart pointer behavior so when an Instance object is no more useful the object
    //! is deleted.
    class Instance : private Smuggler
    {
    public:
        
        //! @brief The constructor for an empty Instance.
        //! @details Creates an Instance that can be used as an empty reference inside
        //! another class.
        Instance() noexcept;
        
        //! @brief The copy constructor.
        //! Creates a copy of an Instance and increments his counter.
        Instance(Instance const& other) noexcept;
        
        //! @brief The move constructor.
        //! @details Creates a copy of an Instance without incrementing his counter. The
        //! other Instance will be useless.
        Instance(Instance&& other) noexcept;
        
        //! @brief The copy operator.
        //! Copies the Instance and increments his counter.
        Instance& operator=(Instance const& other) noexcept;
        
        //! @brief The move operator.
        //! @details Copies the Instance without incrementing his counter. The other
        //! Instance will be destroyed if needed.
        Instance& operator=(Instance&& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Instance will be destroyed if no other copy exists.
        virtual ~Instance() noexcept;
        
        //! @brief Retrieves if the Instance is valid.
        bool isValid() const noexcept;
        
        //! @brief Retrieves the sample rate of the Instance.
        int getSampleRate() const noexcept;
        
        
        
        
        //! @brief Sends a normal post to the Pure Data console.
        void sendConsolePost(std::string const& message) noexcept;
        
        //! @brief Sends a log post to the Pure Data console.
        void sendConsoleLog(std::string const& message) noexcept;
        
        //! @brief Sends an error to the Pure Data console.
        void sendConsoleError(std::string const& message) noexcept;
        
        //! @brief Sends a fatal error to the Pure Data console.
        void sendConsoleFatal(std::string const& message) noexcept;
        
        
        //! @brief Receives a normal post to the Pure Data console.
        virtual void receiveConsolePost(std::string const& message) {};
        
        //! @brief Receives a log post to the Pure Data console.
        virtual void receiveConsoleLog(std::string const& message) {};
        
        //! @brief Receives a error to the Pure Data console.
        virtual void receiveConsoleError(std::string const& message) {};
        
        //! @brief Receives a fatal error to the Pure Data console.
        virtual void receiveConsoleFatal(std::string const& message) {};
    protected:
        
        //! @brief The real constructor.
        Instance(const std::string& name) noexcept;
        
        //! @brief Locks Instance.
        void lock() noexcept;
        
        //! @brief Unlocks Instance.
        void unlock() noexcept;
        
        
        
        
        //! @brief Prepares the digital signal processing chain of the Instance.
        void prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept;
        
        //! @brief Performs the digital signal processing chain of the Instance.
        //! @details You should locks the Instance to ensure thread safety.
        void performDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept;
        
        //! @brief Releases the digital signal processing chain of the Instance.
        void releaseDsp() noexcept;
        
        
        
        //! @brief Sends midi note on.
        void sendMidiNote(int channel, int pitch, int velocity) const;
        
        //! @brief Sends midi control change.
        void sendMidiControlChange(int channel, int controller, int value) const;
        
        //! @brief Sends midi program change.
        void sendMidiProgramChange(int channel, int value) const;
        
        //! @brief Sends midi pitch bend.
        void sendMidiPitchBend(int channel, int value) const;
        
        //! @brief Sends midi after touch.
        void sendMidiAfterTouch(int channel, int value) const;
        
        //! @brief Sends midi poly after touch.
        void sendMidiPolyAfterTouch(int channel, int pitch, int value) const;
        
        //! @brief Sends midi byte.
        void sendMidiByte(int port, int byte) const;
        
        //! @brief Sends midi sys ex.
        void sendMidiSysEx(int port, int byte) const;
        
        //! @brief Sends midi sys real time.
        void sendMidiSysRealtime(int port, int byte) const;
        
        
        
        
        //! @brief Receives midi note on.
        virtual void receiveMidiNoteOn(int channel, int pitch, int velocity) {};
        
        //! @brief Receives midi control change.
        virtual void receiveMidiControlChange(int channel, int control, int value) {}
        
        //! @brief Receives midi program change.
        virtual void receiveMidiProgramChange(int channel, int value) {}
        
        //! @brief Receives midi pitch bend.
        virtual void receiveMidiPitchBend(int channel, int value) {}
        
        //! @brief Receives midi after touch.
        virtual void receiveMidiAfterTouch(int channel, int value) {}
        
        //! @brief Receives midi poly after touch.
        virtual void receiveMidiPolyAfterTouch(int channel, int pitch, int value) {}
        
        //! @brief Receives midi byte.
        virtual void receiveMidiByte(int port, int value) {}
        
        
        
        
        //! @brief Sends bang.
        void sendMessageBang(tie const& name) const;
        
        //! @brief Sends float.
        void sendMessageFloat(tie const& name, float f) const;
        
        //! @brief Sends symbol.
        void sendMessagesymbol(tie const& name, symbol const& s) const;
        
        //! @brief Sends gpointer.
        void sendMessageGpointer(tie const& name, Gpointer const& g) const;
        
        //! @brief Sends list.
        void sendMessageList(tie const& name, List const& list) const;
        
        //! @brief Sends anything.
        void sendMessageAnything(tie const& name, symbol const& s, List const& list) const;
        
        //! @brief Receives bang.
        virtual void receiveMessageBang(tie const& tie) {}
        
        //! @brief Receives float.
        virtual void receiveMessageFloat(tie const& tie, float f) {}
        
        //! @brief Receives symbol.
        virtual void receiveMessagesymbol(tie const& tie, symbol const& s) {}
        
        //! @brief Receives gpointer.
        virtual void receiveMessageGpointer(tie const& tie, Gpointer const& g) {}
        
        //! @brief Receives list.
        virtual void receiveMessageList(tie const& tie, List const& list) {}
        
        //! @brief Receives anything.
        virtual void receiveMessageAnything(tie const& tie, symbol const& s, List const& list) {}
        
    private:
        struct Internal;
        void release() noexcept;
        
        void*               m_ptr;
        std::atomic<long>*  m_count;
        friend class Patch;
        
    };

}

#endif // Z_PD_INSTANCE_HPP
