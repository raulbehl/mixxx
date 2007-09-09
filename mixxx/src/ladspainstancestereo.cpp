/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/

#include <ladspainstancestereo.h>

LADSPAInstanceStereo::LADSPAInstanceStereo(const LADSPA_Descriptor * descriptor) : LADSPAInstance(descriptor)
{
    int sampleRate = getSampleRate();
    qDebug("LADSPA: Sample rate: %d", sampleRate);

    m_Handle = descriptor->instantiate(descriptor, sampleRate);

    if (descriptor->activate)
    {
        descriptor->activate(m_Handle);
    }

    m_InputPortLeft = descriptor->PortCount;
    m_OutputPortLeft = descriptor->PortCount;
    for (unsigned long port = 0; port < descriptor->PortCount; port++)
    {
        qDebug("LADSPA: Port %lu: %s", port, descriptor->PortNames[port]);
        if (LADSPA_IS_PORT_AUDIO(descriptor->PortDescriptors [port]))
        {
            if (LADSPA_IS_PORT_INPUT(descriptor->PortDescriptors [port]))
            {
                if (m_InputPortLeft == descriptor->PortCount)
                {
                    m_InputPortLeft = port;
                }
                else
                {
                    m_InputPortRight = port;
                }
            }
            else
            {
                if (m_OutputPortLeft == descriptor->PortCount)
                {
                    m_OutputPortLeft = port;
                }
                else
                {
                    m_OutputPortRight = port;
                }
            }
        }
    }
    qDebug("LADSPA: Input: %lu, %lu", m_InputPortLeft, m_InputPortRight);
    qDebug("LADSPA: Output: %lu, %lu", m_OutputPortLeft, m_OutputPortRight);
}

LADSPAInstanceStereo::~LADSPAInstanceStereo()
{
    if (getDescriptor()->deactivate)
    {
        getDescriptor()->deactivate(m_Handle);
    }

    getDescriptor()->cleanup(m_Handle);
}

void LADSPAInstanceStereo::process(const CSAMPLE * pInLeft, const CSAMPLE * pInRight, const CSAMPLE * pOutLeft, const CSAMPLE * pOutRight, const int iBufferSize)
{
    getDescriptor()->connect_port(m_Handle, m_InputPortLeft, (LADSPA_Data *) pInLeft);
    getDescriptor()->connect_port(m_Handle, m_OutputPortLeft, (LADSPA_Data *) pOutLeft);
    getDescriptor()->connect_port(m_Handle, m_InputPortRight, (LADSPA_Data *) pInRight);
    getDescriptor()->connect_port(m_Handle, m_OutputPortRight, (LADSPA_Data *) pOutRight);
    getDescriptor()->run(m_Handle, iBufferSize);
}

void LADSPAInstanceStereo::connect(unsigned long port, LADSPA_Data * buffer)
{
    getDescriptor()->connect_port(m_Handle, port, buffer);
}
