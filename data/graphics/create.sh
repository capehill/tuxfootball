#!/bin/sh

for COLOR in "1.0, 0.0, 0.0" "0.0, 0.0, 1.0"; do
	TEAMDIR="failed"
	if [ "1.0, 0.0, 0.0" = "${COLOR}" ]; then
		TEAMDIR="team2"
	elif [ "0.0, 0.0, 1.0" = "${COLOR}" ]; then
		TEAMDIR="team1"
	fi
	if [ "${TEAMDIR}" = "failed" ]; then
		echo "Failed to find team dir"
		exit 1
	fi
	for DEGREE in 0 45 90 135 180 225 270 315; do
		echo "Creating ${DEGREE}° perspective"
		sed -e "s:XX_DEGREE_XX:${DEGREE}:g" -e "s:XX_COLOR_XX:${COLOR}:g" rotate.py > rotate${DEGREE}.py
		blender -P rotate${DEGREE}.py
		TARGETDIR='failed'
		if [ "${DEGREE}" = "0" ]; then
			TARGETDIR="se"
		elif [ "${DEGREE}" = "45" ]; then
			TARGETDIR="e"
		elif [ "${DEGREE}" = "90" ]; then
			TARGETDIR="ne"
		elif [ "${DEGREE}" = "135" ]; then
			TARGETDIR="n"
		elif [ "${DEGREE}" = "180" ]; then
			TARGETDIR="nw"
		elif [ "${DEGREE}" = "225" ]; then
			TARGETDIR="w"
		elif [ "${DEGREE}" = "270" ]; then
			TARGETDIR="sw"
		elif [ "${DEGREE}" = "315" ]; then
			TARGETDIR="s"
		fi
		if [ "${TARGETDIR}" = "failed" ]; then
			echo "Failed to find target dir"
			exit 1
		fi
		blender -b player${DEGREE}.blend -o ${TEAMDIR}/standing/${TARGETDIR}/standing -f 1
		blender -b player${DEGREE}.blend -o ${TEAMDIR}/walking/${TARGETDIR}/walking -s 10 -e 49 -a
		rm -f player${DEGREE}.blend rotate${DEGREE}.py
	done
done

echo "All done"

exit 0
