#ifndef NTP_H
#define NTP_H

#include <NTPClient.h>
#include <WiFiUdp.h>

// ============================================================================
// NTP Server Settings

const char* ntpServerName = "time.nist.gov"; // NTP Server Name
const int localTimeOffset = -18000;           // Time in seconds from UTC
const int utcTimeOffset   = 0;                // UTC Time Offset

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServerName, 0, 60000); // Update interval set to 60 seconds

// ============================================================================
// ============================================================================
// Setup
// ============================================================================

void setupNTP() {
    timeClient.begin();
    timeClient.setTimeOffset(localTimeOffset);
}

// ============================================================================
// ============================================================================
// Update
// ============================================================================

void updateNTP() {
    timeClient.update();
}

// ====================================
// Get Functions
// ====================================

String getFormattedTime() {
    return timeClient.getFormattedTime();
}

int getCurrentSeconds() {
    return timeClient.getSeconds();
}

int getCurrentMinutes() {
    return timeClient.getMinutes();
}

int getCurrentHour() {
    return timeClient.getHours();
}

unsigned long getEpochTime() {
    return timeClient.getEpochTime();
}

String getUptime()
{
	unsigned long millisec = millis();
	unsigned long seconds = millisec / 1000;
	unsigned long minutes = seconds / 60;
	unsigned long hours = minutes / 60;

	seconds = seconds % 60;
	minutes = minutes % 60;
	hours = hours % 24;

	char uptime[9];
	snprintf(uptime, sizeof(uptime), "%02lu:%02lu:%02lu", hours, minutes, seconds);
	return String(uptime);
}

#endif // NTP_H