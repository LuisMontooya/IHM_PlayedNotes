#pragma once

#include <JuceHeader.h>
using namespace std;
using namespace juce;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component,
                       public Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    void buttonClicked (Button* button) override;

    //==============================================================================
    void paint(juce::Graphics&) override {
        addAndMakeVisible(sound_list);
        sound_list.onChange = [this]() { soundListChanged(); };

        // Listen chosen sound
        addAndMakeVisible(listen_sound);
        listen_sound.onClick = [this]() { playSound(); };

        record_button.setToggleState(true, NotificationType::dontSendNotification);
        record_button.onClick = [this]() { start_record(); };
        record_button.setColour(TextButton::ColourIds::buttonColourId, Colours::limegreen);
        record_button.setColour(TextButton::ColourIds::buttonColourId, Colours::indianred);
        record_button.addListener(this);
        addAndMakeVisible(record_button);
        
        addAndMakeVisible(tempoLabel);
        tempoLabel.setFont(juce::Font(16.0f, juce::Font::bold));
        tempoLabel.setText("Enter Tempo:" , juce::dontSendNotification);
        addAndMakeVisible(enter_tempo);
        enter_tempo.setInputRestrictions(3,"0123456789");

        addAndMakeVisible(note_1);
        note_1.onClick = [this]() { addNote(1); };
        addAndMakeVisible(note_2);
        note_2.onClick = [this]() { addNote(2); };
        addAndMakeVisible(note_3);
        note_3.onClick = [this]() { addNote(3); };

        addAndMakeVisible(notesPlayed);
        notesPlayed.setFont(juce::Font(12.0f, juce::Font::bold));
        notesPlayed.setText("Notes Played:", juce::dontSendNotification);
        addAndMakeVisible(display_notes);
        display_notes.setReadOnly(true);
        addAndMakeVisible(consoleDisplay);
        consoleDisplay.setFont(juce::Font(12.0f, juce::Font::bold));
        consoleDisplay.setText("Console Activity:", juce::dontSendNotification);
        addAndMakeVisible(display_pattern);

        addAndMakeVisible(sendSequence);
        sendSequence.onClick = [this]() { connectWhiteBoard();  };
    };

    void resized() override {
        sound_list.addItem("Boom", 1);
        sound_list.addItem("Clap", 2);
        sound_list.addItem("Shak", 3);

        sound_list.setBounds(getWidth() / 4 - 20, getHeight() / 2 - 175, getWidth() / 4 , 20);
        listen_sound.setBounds(getWidth() / 4 + 200, getHeight() / 2 - 175, getWidth() / 4, 20);

        tempoLabel.setBounds(getWidth() / 2 - 120, getHeight() / 2 - 125, getWidth() / 4, 20);
        enter_tempo.setBounds(getWidth() / 2 , getHeight() / 2 - 125, getWidth() / 4 , 20);

        record_button.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 85, getWidth() / 4 , 20);

        note_1.setBounds(getWidth() / 4 - 60 , getHeight() / 2 - 50, getWidth() / 4, 20);
        note_2.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 50, getWidth() / 4, 20);
        note_3.setBounds(3 * getWidth() / 4 - 40 , getHeight() / 2 - 50, getWidth() / 4, 20);

        notesPlayed.setBounds(getWidth() / 4 - 100, getHeight() / 2 - 12, getWidth() / 4, 20);
        display_notes.setBounds(getWidth() / 4 - 10, getHeight() / 2 - 10, getWidth() / 2 + 50, 50);
        consoleDisplay.setBounds(getWidth() / 4 - 120, getHeight() / 2 + 79, getWidth() / 4, 20);
        display_pattern.setBounds(getWidth() / 4 - 10, getHeight() / 2 + 80, getWidth() / 2 + 50, 50);

        sendSequence.setBounds(getWidth() / 2 - 50, getHeight() / 2 + 140, getWidth() / 4, 20);
    };

    void soundListChanged() {
        switch (sound_list.getSelectedId())
        {
        case 1:  
            sound_list.setSelectedId(1);  
            break;
        case 2:  
            sound_list.setSelectedId(2);
            break;
        case 3:  
            sound_list.setSelectedId(3); 
            break;
        }
    };

    void playSound() {

    };

    void start_record() {
        playState = PlayState::Play;
        record_button.setToggleState(false, NotificationType::dontSendNotification);
        record_button.setButtonText("Recording");
        display_notes.insertTextAtCaret("||-->");
        Logger::outputDebugString("Press Play");
    };

    void stop_record() {
        playState = PlayState::Stop;
        record_button.setToggleState(true, NotificationType::dontSendNotification);
        record_button.setButtonText("Stopped");
        display_notes.insertTextAtCaret("<--||") ;
        Logger::outputDebugString("Press Stop");
    };

    void addNote(int note) {
        Logger::outputDebugString(String(note));
        display_notes.insertTextAtCaret(String(note) + "-");
    };

    void connectWhiteBoard() {
        Logger::outputDebugString("Send sequence to WhiteBoard");

    };


private:
    //==============================================================================
    // Your private member variables go here...

    enum class PlayState
    {
        Play,
        Stop
    };

    juce::ComboBox sound_list;
    juce::TextButton listen_sound{"Listen Sequence"};

    PlayState playState{ PlayState::Stop };
    juce::TextButton record_button{"Start Recording"};
    
    juce::Label tempoLabel;
    juce::TextEditor enter_tempo;

    juce::TextButton note_1{ "Boom" };
    juce::TextButton note_2{ "Clap" };
    juce::TextButton note_3{ "Shak" };

    juce::Label notesPlayed;
    juce::TextEditor display_notes;
    juce::Label consoleDisplay;
    juce::TextEditor display_pattern;

    juce::TextButton sendSequence{ "Send sequence" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
