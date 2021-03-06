#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}


void MainComponent::buttonClicked(Button* button) 
{
    if (button == &record_button)
    {
        if (playState == PlayState::Stop)
        {
            record_button.onClick = [this]() { start_record(); };
            record_button.setColour(TextButton::ColourIds::buttonColourId, Colours::limegreen); // not working
        }
        else if (playState == PlayState::Play)
        {
            record_button.onClick = [this]() { stop_record(); };
            record_button.setColour(TextButton::ColourIds::buttonColourId, Colours::indianred); // not working
        }
    }
}

//==============================================================================
/*void MainComponent::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

/*void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
*/