# https://school.programmers.co.kr/learn/courses/30/lessons/92341
import json

calculated = []
parkingDurationHistory = []
didParkedToday = False

def solution(fees, records):
    answer = []

    baseTime = fees[0]
    baseCharge = fees[1]
    unitTime = fees[2]
    unitCharge = fees[3]

    numberOfRecords = len(records)
    recordList = []

    for record in records:
        timestamp, plateNumber, inout = record.split(" ")
        recordDict = {"plateNumber": plateNumber, "timestamp": timestamp, "inout": inout}
        recordList.append(recordDict)

    historyOrderByPlateNumber = handleInAndOut(recordList)
    plateNumberHistory = historyOrderByPlateNumber.keys()

    for plateNumber in plateNumberHistory:
        compressParkedTime(historyOrderByPlateNumber[plateNumber])
        calculateCharge(plateNumber, baseTime, baseCharge, unitTime, unitCharge)

    for receipt in calculated:
        answer.append(receipt["fee"])
        
    # print("Parking Fee for " + plateNumber + " : " + str(fee))
    return answer

def handleInAndOut(recordList):
    organizedHistory = {}
    
    for record in recordList:
        plateNumber = record["plateNumber"]
        if plateNumber not in organizedHistory:
            organizedHistory[plateNumber] = []
        organizedHistory[plateNumber].append(record)

    return organizedHistory

def calculateCharge(plateNumber, baseTime, baseCharge, unitTime, unitCharge):
    global calculated
    global didParkedToday
    global parkingDurationHistory

    fee = 0
    parkingDuration = 0

    for history in parkingDurationHistory:
        if history["plateNumber"] == plateNumber:
            parkingDuration += history["parkedDuration"]
    if parkingDuration <= baseTime:
        fee = baseCharge
    else:
        # 기본 시간을 초과한 경우, baseTime을 제외한 duration에 대해 단위 요금제 적용
        if (parkingDuration - baseTime) % unitTime == 0:
            fee = baseCharge + ((parkingDuration - baseTime) // unitTime) * unitCharge
        else:
            fee = baseCharge + (((parkingDuration - baseTime) // unitTime) + 1) * unitCharge

    # print("parkingDuration : " + str(parkingDuration))
    calculated.append({"plateNumber": plateNumber, "fee": fee})
    calculated = sorted(calculated, key=lambda k: k["plateNumber"])
    return calculated

def compressParkedTime(historyDict):
    global calculated
    global didParkedToday
    global parkingDurationHistory

    isCarParked = False
    timeIn, timeOut, parkedDuration = "", "", 0

    for history in historyDict:
        if history["inout"] == "IN":
            isCarParked = True
            timeIn = history["timestamp"]
            # historyDict.pop(historyDict.index(history))
        else:
            isCarParked = False
            timeOut = history["timestamp"]
            # historyDict.pop(historyDict.index(history))
        
        # 입차 후 출차 기록이 확인된 경우, timeIn과 timeOut을 이용하여 주차 시간 계산
        if isCarParked == False:
            parkedDuration = calculateParkedTime(timeIn, timeOut)
            
        # 입차 후 출고 기록이 없고 현재 기록이 마지막 기록인 경우, timeIn과 일마감을 이용하여 주차 시간 계산
        if isCarParked == True and history == historyDict[-1]:
            timeOut = "23:59"
            parkedDuration = calculateParkedTime(timeIn, timeOut)
            
        if parkedDuration != 0:
            parkingDurationHistory.append({"plateNumber": history["plateNumber"], "parkedDuration": parkedDuration})
            parkedDuration = 0
        
    # print("parkingDurationHistory : \n" + str(json.dumps(parkingDurationHistory, indent=4)))    
    # for history in parkingDurationHistory:
        


    timeIn, timeOut = "", ""
    didParkedToday = True
            

def calculateParkedTime(timeIn, timeOut):
    timeInHour, timeInMinute = timeIn.split(":")
    timeOutHour, timeOutMinute = timeOut.split(":")

    parkedDuration = (int(timeOutHour) - int(timeInHour)) * 60 + (int(timeOutMinute) - int(timeInMinute))

    return parkedDuration


def main():
    fees = [180, 5000, 10, 600]
    records = ["05:34 5961 IN", "06:00 0000 IN", "06:34 0000 OUT",
               "07:59 5961 OUT", "07:59 0148 IN", "18:59 0000 IN",
               "19:09 0148 OUT", "22:59 5961 IN", "23:00 5961 OUT"]
    print(solution(fees, records))

if __name__ == "__main__":
    main()
