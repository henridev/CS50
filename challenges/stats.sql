SELECT TagName, CNT, Rep
FROM (
  SELECT TagName, count(*) as CNT, AVG(Cast(rep as Float)) as Rep
    FROM (
      SELECT p.id, T.TagName, u.Reputation as rep
      from posts as p
      inner join PostTags as pt on pt.PostId=p.Id
      inner join Tags as t on t.Id=pt.TagId
      inner join Users as u on u.Id=p.OwnerUserId
    ) as t1
  group by TagName
  ) as t2
WHERE TagName LIKE 'reactjs'
  OR TagName LIKE 'angular'
  OR TagName LIKE 'vue.js%'