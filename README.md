# MPU-69
Under development as of Jan 2025. Please reach out if you'd like to help.

The MPU-69 is/will be an open source IP based MANET(Mobile Ad-hoc Network) system similiar to the mega-gucci MPU-5, but built for the poors. Obviously data rates and range will not be comparible. Ruggedized radio that can deliver more data than meshtestic is the goal. 

The radio hardware will be built around an array (1-3) of affordable si4463 radio modules coupled to an MCU (likely NUCLEO) to provide radio control. This will first accomidate UHF 420-450mhz but will add other bands doiwn the road (2m, 800-900, 2.5g, etc)

The firmware heavily leverages "New Packet Radio" system found here: https://hackaday.io/project/164092-npr-new-packet-radio

NPR is a well developed ham network used in europe. This NPR system consists of custom pcb boards with rf4463 chips thag pass ip packets around at up to 500kb/s. Since its ham it has no enceyptrion or any real practical use in a mobile environment. This project will adapt NPR into a more mobile friendly arcitecture creating the ultimate larp comms kits.

Use cases:
- VoIP/RoIP
- ATAK multicast comms
- Streaming video/picture feed to multiple users
- Robot/uav control
- Remote control or a marauder-32 or other pen tools
- Data package transfer
- Getting tinder dates in a contested ew environment

Objectives:
- Add encryption and over the air re-keying.
- Add mesh networking (curently master/client system likited to 8 users). Needs to be self healing.
- Implement 5-10w power amplifier to hardwre design
- MIMO for increased througput
- Redesign pcb and package into mobile housing similiar to existing mpu-5. make compatible with prc-148 batteries.

