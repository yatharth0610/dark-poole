---
layout: default
title: Archive
---

# Blog

This is where I will be writing some tutorials as well as experiences that I think are worth sharing. I will also try to write some personal blogs here, which you might (not) find interesting. 

{% assign postsByYearMonth = site.posts | group_by_exp: "post", "post.date | date: '%B %Y'" %}
{% for yearMonth in postsByYearMonth %}

  <h2>{{ yearMonth.name }}</h2>
  <ul>
    {% for post in yearMonth.items %}
      <li><a href="{{ site.baseurl }}{{ post.url }}">{{ post.title }}</a></li>
    {% endfor %}
  </ul>
{% endfor %}
