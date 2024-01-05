import json

calculated = []
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
        fee = calculateCharge(historyOrderByPlateNumber[plateNumber], baseTime, baseCharge, unitTime, unitCharge)
        print("Parking Fee for " + plateNumber + " : " + str(fee))

    return answer

def handleInAndOut(recordList):
    organizedHistory = {}
    
    for record in recordList:
        plateNumber = record["plateNumber"]
        if plateNumber not in organizedHistory:
            organizedHistory[plateNumber] = []
        organizedHistory[plateNumber].append(record)
    print("organizedHistory : \n" + str(json.dumps(organizedHistory, indent=4)))

    return organizedHistory
            

def calculateCharge(historyDict, baseTime, baseCharge, unitTime, unitCharge):
    global calculated
    global didParkedToday
    isCarParked = False
    timeIn, timeOut, parkedDuration = "", "", 0
    charged = 0

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
            if parkedDuration <= baseTime & didParkedToday == False:
                charged = baseCharge
            else:
                # 첫 출차라면 기본 요금 깐 다음에, 남은 시간에 대한 요금 계산
                if didParkedToday == False:
                    charged += baseCharge
                    parkedDuration -= baseTime
                    if parkedDuration % unitTime != 0:
                        charged += (parkedDuration // unitTime + 1) * unitCharge
                    else:
                        charged += (parkedDuration // unitTime) * unitCharge
                else: # 이미 출차한 적이 있다면, 남은 시간에 대한 요금 계산
                    if parkedDuration % unitTime != 0:
                        charged += (parkedDuration // unitTime + 1) * unitCharge
                    else:
                        charged += (parkedDuration // unitTime) * unitCharge

        if isCarParked == True and history == historyDict[-1]:
            timeOut = "23:59"
            parkedDuration = calculateParkedTime(timeIn, timeOut)
            if parkedDuration <= baseTime & didParkedToday == False:
                charged = baseCharge
            else:
                # 첫 출차라면 기본 요금 깐 다음에, 남은 시간에 대한 요금 계산
                if didParkedToday == False:
                    charged += baseCharge
                    parkedDuration -= baseTime
                    if parkedDuration % unitTime != 0:
                        charged += (parkedDuration // unitTime + 1) * unitCharge
                    else:
                        charged += (parkedDuration // unitTime) * unitCharge
                else: # 이미 출차한 적이 있다면, 남은 시간에 대한 요금 계산
                    if parkedDuration % unitTime != 0:
                        charged += (parkedDuration // unitTime + 1) * unitCharge
                    else:
                        charged += (parkedDuration // unitTime) * unitCharge

        calculated.append({"plateNumber": history["plateNumber"], "charged": charged})



    timeIN, timeOut = "", ""
    didParkedToday = True
    return charged
            

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
