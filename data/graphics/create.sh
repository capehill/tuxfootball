#!/bin/sh

echo "" > create.log

render() {
	TEAMDIR=${1}
	DEGREE=${2}
	TARGETDIR=${3}
	ANIMATION=${4}
	FROM=${5}
	TO=${6}
	echo "Creating ${TEAMDIR} ${DEGREE}° ${ANIMATION}"
	echo "Creating ${TEAMDIR} ${DEGREE}° ${ANIMATION}" >> create.log
	if [ "" = "${TO}" ]; then
		blender -b player${DEGREE}.blend -o ${TEAMDIR}/${ANIMATION}/${TARGETDIR}/${ANIMATION} -f ${FROM} >> create.log
	else
		blender -b player${DEGREE}.blend -o ${TEAMDIR}/${ANIMATION}/${TARGETDIR}/${ANIMATION} -s ${FROM} -e ${TO} -a >> create.log
	fi
	for X in `seq ${FROM} ${TO}`; do
		TARGET=`expr ${X} - ${FROM} + 1`
		if [ ${TARGET} -lt 10 ]; then
			TO_FIX='0'
		else
			TO_FIX=''
		fi
		if [ ${X} -lt 10 ]; then
			FROM_FIX='000'
		else
			if [ ${X} -lt 100 ]; then
				FROM_FIX='00'
			else
				FROM_FIX='0'
			fi
		fi
		if [ "${TEAMDIR}/${ANIMATION}/${TARGETDIR}/${ANIMATION}${FROM_FIX}${X}" != "${TEAMDIR}/${ANIMATION}/${TARGETDIR}/${ANIMATION}00${TO_FIX}${TARGET}" ]; then
			mv ${TEAMDIR}/${ANIMATION}/${TARGETDIR}/${ANIMATION}${FROM_FIX}${X}.png ${TEAMDIR}/${ANIMATION}/${TARGETDIR}/${ANIMATION}00${TO_FIX}${TARGET}.png
		fi
	done

}

for COLOR in "0.0, 0.0, 1.0" "1.0, 0.0, 0.0"; do
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
		render ${TEAMDIR} ${DEGREE} ${TARGETDIR} 'standing' 1
		render ${TEAMDIR} ${DEGREE} ${TARGETDIR} 'walking' 10 49
		render ${TEAMDIR} ${DEGREE} ${TARGETDIR} 'running' 60 99
		render ${TEAMDIR} ${DEGREE} ${TARGETDIR} 'tackling' 110 134
		rm -f player${DEGREE}.blend rotate${DEGREE}.py
	done
done

echo "Optimizing PNGs"
echo "Optimizing PNGs" >> create.log

find team1 -name "*.png" | xargs optipng >> create.log
find team2 -name "*.png" | xargs optipng >> create.log

echo "All done"

exit 0
