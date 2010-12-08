#!/bin/sh

echo "" > create.log

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
		echo "Creating ${TEAMDIR} ${DEGREE}° perspective"
		echo "Creating ${TEAMDIR} ${DEGREE}° perspective" >> create.log
		sed -e "s:XX_DEGREE_XX:${DEGREE}:g" -e "s:XX_COLOR_XX:${COLOR}:g" rotate.py > rotate${DEGREE}.py
		blender -P rotate${DEGREE}.py >> create.log
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
		echo "Creating ${TEAMDIR} ${DEGREE}° standing"
		echo "Creating ${TEAMDIR} ${DEGREE}° standing" >> create.log
		blender -b player${DEGREE}.blend -o ${TEAMDIR}/standing/${TARGETDIR}/standing -f 1 >> create.log
		echo "Creating ${TEAMDIR} ${DEGREE}° walking"
		echo "Creating ${TEAMDIR} ${DEGREE}° walking" >> create.log
		blender -b player${DEGREE}.blend -o ${TEAMDIR}/walking/${TARGETDIR}/walking -s 10 -e 49 -a >> create.log
		for X in `seq 10 49`; do
			TARGET=`expr ${X} - 9`
			if [ ${TARGET} -lt 10 ]; then
				mv ${TEAMDIR}/walking/${TARGETDIR}/walking00${X}.png ${TEAMDIR}/walking/${TARGETDIR}/walking000${TARGET}.png
			else
				mv ${TEAMDIR}/walking/${TARGETDIR}/walking00${X}.png ${TEAMDIR}/walking/${TARGETDIR}/walking00${TARGET}.png
			fi
		done
		echo "Creating ${TEAMDIR} ${DEGREE}° running"
		echo "Creating ${TEAMDIR} ${DEGREE}° running" >> create.log
		blender -b player${DEGREE}.blend -o ${TEAMDIR}/running/${TARGETDIR}/running -s 60 -e 99 -a >> create.log
		for X in `seq 60 99`; do
			TARGET=`expr ${X} - 59`
			if [ ${TARGET} -lt 10 ]; then
				mv ${TEAMDIR}/running/${TARGETDIR}/running00${X}.png ${TEAMDIR}/running/${TARGETDIR}/running000${TARGET}.png
			else
				mv ${TEAMDIR}/running/${TARGETDIR}/running00${X}.png ${TEAMDIR}/running/${TARGETDIR}/running00${TARGET}.png
			fi
		done
		rm -f player${DEGREE}.blend rotate${DEGREE}.py
	done
done

echo "All done"

exit 0
